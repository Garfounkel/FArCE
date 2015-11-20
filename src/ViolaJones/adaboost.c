#include "adaboost.h"

Triplet create_Triplet(Ulong_tab* img, int weight, int is_a_face)
{
  Triplet triplet;
  triplet.img = img;
  triplet.weight = weight;
  triplet.is_a_face = is_a_face;

  return triplet;
}




// Images list:
size_t dirLenght(char* path){
  DIR *dir;
  struct dirent *ent;
  size_t nbr = 0;
  if ((dir = opendir(path)) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
        nbr++;
    }
    closedir(dir);
  }

  return nbr;
}

char** get_Files_List(char* path, size_t *nb){
printf ("oppening %s\n",path);
  DIR *dir;
  struct dirent *ent;
  size_t pathLenght = strlen(path);
  if ((dir = opendir(path)) != NULL) {
    size_t lenght = dirLenght(path);
    char **list = malloc(sizeof(char*) * (lenght + 1));
    size_t i = 0;
    while((ent = readdir(dir)) != NULL){
      char *fileName = ent->d_name;
      if (strcmp(fileName, ".") != 0 && strcmp(fileName, "..") != 0){
        size_t slenght = strlen(fileName);
        list[i] = malloc(pathLenght + slenght + 2);
        snprintf(list[i], (pathLenght + slenght + 2), "%s/%s", path, fileName);
        i++;
      }
    }
    closedir(dir);
    *nb = i;
    return list;
  }
  else {
    *nb = 0;
    printf("Couldn't open directory :(\n");
    return NULL;
  }
}

void print_images_list(char **list, size_t lenght){
  if (list == NULL) {
    printf("list is empty :(\n");
    return;
  }
  printf("List of files:\n");
  for (size_t i = 0; i < lenght; i++) {
    printf("%s\n", list[i]);
  }
}

// Load an image
SDL_Surface* load_img(char *path)
{

  SDL_Surface          *img;

  // Load an image using SDL_image with format detection
  img = IMG_Load(path);

  if (!img)
    // If it fails, die with an error message
    errx(3, "can't load %s: %s", path, IMG_GetError());

  return img;

}


void generate_Triplet_vect(char* directory, Triplet** imgs, size_t* size)
{
  char** file_list = get_Files_List(directory, size);

  for (size_t i = 0; i < *size; ++i)
    printf ("%zu %s \n", i, file_list[i] + 19);// == 'f');

  printf ("%zu\n",*size);

  *imgs = malloc(sizeof(Triplet) * *size);

  for (size_t i = 0; i < *size; ++i)
  {

    SDL_Surface* img = preprocessing(load_img(file_list[i]));
    Ulong_tab* tab   = create_Ulong_tab(img->h, img->w);

    integral_image(img, tab);

    (*imgs)[i].img       = tab;
    printf ("size = %zu | 1/size = %f\n",*size,(double)((double)(1) / (double)(*size)));
    assert((*imgs)[i].weight    = (double)((double)(1) / (double)(*size)));

    (*imgs)[i].is_a_face = *file_list[i] == 'f' ? 1 : -1;
  }
}



void write_model(Model* m, char* fname)
{
  if (m)
  {
    FILE *file;
    // open file in create/replace mode
    if ((file = fopen(fname, "w")) == NULL)
    {
      warnx("error ");
      err(3, "Error while creating %s", fname);
    }


    for (int i = 0; i < 160337; ++i)
    {
      if (m->coefs[i])
        warnx("%s>%f\n", Haar_to_str(m->haars[i]), m->coefs[i]);
      fprintf(file, "%s>%f\n", Haar_to_str(m->haars[i]), m->coefs[i]);
    }

    // close the file
    fclose(file);
  }
}


// Adaboost pseudo-code:

Model adaboost(Triplet* imgs, size_t len_imgs)
{
  Model model;
  model.coefs = calloc(160336, sizeof(double));
  model.haars = malloc(sizeof(Haar)  * 160336);

  write_model(&model, "model.farce");

  size_t size_features;
  Haar* features = compute_haar_features(imgs->img, &size_features);
  int iterations = 0;

  //il ne s'arret que quand optimisation impossble
  while (1)
  {
    //warnx("adaboost next level\n");
    int min = 0;
    Haar haar_min;
    double errormin = 1;

    for (size_t f = 0; f < size_features; ++f)
    {
      //warnx("feature\n");

      // 73440 = val max d'une sum en 24x24
      for (features[f].threshold = -73440;
           features[f].threshold <  73440;
           features[f].threshold += 10000)
      {
        //warnx("threshold\n");

        double error = 1;
        //parcour le tableau d'image
        for (Triplet* i = imgs; i < imgs + len_imgs; i++)
        {
          /*warnx("it = %d | feature = %d | threshold = %6d | img = %d\n",
                iterations,
                f,
                features[f].threshold,
                (int)(i - imgs));
          */
//valeur de l'haar
          compute_haar_sum(i->img, &features[f]);
          features[f].polarity = 1;

          // calcul l'erreur de l'Haar
          assert(i->weight);

          error +=
            i->weight    *
            i->is_a_face *
            is_present(features[f]);
        }
        //s'assur que l'erreur min soit bien la minimal
        if (error < errormin)
        {
          errormin          = error;
          copy_Haar(&features[f], &haar_min);
          //haar_min          = features[f];
          haar_min.polarity = 1;
          min               = f;
        }
        else if (1/error < errormin)
        {
          errormin          = 1/error;
          copy_Haar(&features[f], &haar_min);
          //haar_min          = features[f];
          haar_min.polarity = -1;
          min               = f;
        }
      }
      /* if (f%200 == 0)
	 warnx("it = %d | feature = %zu\n",iterations, f);*/

    }
    warnx("error min");

    //verifie si on peut utilise l'haar
    if (errormin >= 0.5)
    {
      warnx("write modele fin\n");

      write_model(&model, "model.farce");
      return model;
    }

    warnx("calc coef\n");

    if(errormin == 0)
    {
      warnx("ERRROR MIN ERROR MIN ERROR MIN");
    }

    warnx("%f", errormin);
    model.coefs[min] = 1/2*log((1 - errormin)/errormin);

    warnx("asigne haar\n");

    model.haars[min] = haar_min;
    // on ajoute le model
    for (Triplet* i = imgs; i < imgs + len_imgs; ++i)
    {
      warnx("def poids img n°%zu\n", i - imgs);

      assert(i->weight =
             i->weight *

             exp(
               -model.coefs[min] *
               i->is_a_face      *
               is_present(haar_min))

             /

             (2*sqrt(errormin*(1 - errormin))));

    }

    warnx("write model\n");
    write_model(&model, "model.farce");
    warnx("it = %d\n",iterations);
    iterations++;
  }
}
