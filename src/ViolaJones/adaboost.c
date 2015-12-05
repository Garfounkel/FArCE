// Caracteristique = (threshold, toggle, error, margin)

#include "adaboost.h"

Triplet create_Triplet(Ulong_tab* img, int weight, int is_a_face)
{
  Triplet triplet;
  triplet.img = img;
  triplet.weight = weight;
  triplet.is_a_face = is_a_face;

  return triplet;
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

    for (int i = 0; i < 162336; ++i)
    {
      if (m->coefs[i])
        warnx("%s>%f\n", Haar_to_str(m->haars[i]), m->coefs[i]);

      fprintf(file, "%s>%f\n", Haar_to_str(m->haars[i]), m->coefs[i]);
    }

    // close the file
    fclose(file);
  }
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
  warnx("oppening %s\n",path);
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
    warnx("Couldn't open directory :(\n");
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

  //for (size_t i = 0; i < *size; ++i)
  //printf ("%zu %s \n", i, file_list[i] + 19);// == 'f');

  printf ("%zu\n",*size);

  *imgs = malloc(sizeof(Triplet) * *size);

  for (size_t i = 0; i < *size; ++i)
  {

    SDL_Surface* img = preprocessing(load_img(file_list[i]));
    Ulong_tab* tab   = create_Ulong_tab(img->h, img->w);

    integral_image(img, tab);

    (*imgs)[i].img       = tab;
    //printf ("size = %zu | 1/size = %f\n",*size,(double)((double)(1) / (double)(*size)));
    assert((*imgs)[i].weight    = (double)((double)(1) / (double)(*size)));

    (*imgs)[i].is_a_face = file_list[i][19] == 'f' ? 1 : -1;

    warnx("%s, %s\n", ((*imgs)[i].is_a_face + 1)?"face":"non face", file_list[i] + 19 );

  }
}

// algorithme 4

Caracteristique find_Decision_Stump(Triplet* train_exp, size_t n) {

  int t = 0; // Treshold
  for (size_t i = 0; i < n; i++) {
    if (train_exp[i].sum - 1 < t)
      t = train_exp[i].sum - 1;
  }
  //warnx("init t = %d", t);


  int M = 0; // Margin
  float error = 2; // Error

  //Sum up the weights of the positive (resp. negative) examples whose f-th feature is bigger than the present threshold
  float WpSup = 0;
  float WnSup = 0;
  float WpInf = 0;
  float WnInf = 0;
  for (size_t i = 0; i < n; i++) {

    //warnx("%d", train_exp[i].sum);

    if (train_exp[i].sum > t)
    {
      if (train_exp[i].is_a_face == 1) {
        WpSup += train_exp[i].weight;
      }
      else {
        WnSup += train_exp[i].weight;
      }
    }
    else {
      if (train_exp[i].is_a_face == 1) {
        WpInf += train_exp[i].weight;
      }
      else {
        WnInf += train_exp[i].weight;
      }
    }


    /*
    if (train_exp[i].is_a_face) {
      if (train_exp[i].sum > t)
        WpSup += train_exp[i].weight;
      else
        WpInf += train_exp[i].weight;
    }
    else {
      if (train_exp[i].sum > t)
        WnSup += train_exp[i].weight;
      else
        WnInf += train_exp[i].weight;
    }
    */
  }



  //assert(WnInf > 0);
  //assert(WnSup > 0);
  //assert(WpInf > 0);
  //assert(WpSup > 0);

  //warnx("WnInf = %f", WnInf);
  //warnx("WnSup = %f", WnSup);
  //warnx("WpInf = %f", WpInf);
  //warnx("WpSup = %f", WpSup);

  size_t j = 0;
  int tbar = t;
  int Mbar = M;
  int T;

  while (1) {
    float errorp = WpInf + WnSup;
    float errorn = WpSup + WnInf;
<<<<<<< HEAD
    if (errorn == 0 || errorp == 0) {
      warnx("error feature");
      break;
    }
    assert(errorp > 0);
    assert(errorn > 0);

    T = errorp < errorn ? 1 : -1;

=======
    T = errorp > errorn ? 1 : -1;

>>>>>>> 8c414f206abea192fe392a669582a75fb169afcb
    float errorbar;
    int Tbar;

    if (errorp < errorn)
    {
      errorbar = errorp;
      Tbar = 1;
    }
    else
    {
      errorbar = errorn;
      Tbar = -1;
    }

    if (errorbar < error || (errorbar == error && Mbar > M))
    {
      error = errorbar;
      t = tbar;
      M = Mbar;
      T = Tbar;
    }

    if (j == n) {
      break;
    }
    j++;

    while (1) {
      if (train_exp[j].is_a_face == -1)
      {
        WnInf += train_exp[j].weight;
        WnSup -= train_exp[j].weight;
      }
      else
      {
        WpInf += train_exp[j].weight;
        WpSup -= train_exp[j].weight;
      }

      if (j == n || train_exp[j].sum != train_exp[j + 1].sum) {
        break;
      }
      else {
        j++;
      }
    }

    if (j == n) {
      for (size_t i = 0; i < n; i++)
<<<<<<< HEAD
        if (train_exp[i].sum + 1 > tbar)
=======
        if (train_exp[i].sum > t)
>>>>>>> 8c414f206abea192fe392a669582a75fb169afcb
          tbar = train_exp[i].sum + 1;
      Mbar = 0;
    }
    else {
      tbar = (train_exp[j].sum + train_exp[j + 1].sum)/2;
      Mbar = train_exp[j + 1].sum - train_exp[j].sum;
    }
  }
  Caracteristique c;
  c.error = error;
  warnx("error = %f", error);
  c.toggle = T;
  c.threshold = t;
  c.margin = M;
  return c;
}


size_t Best_stump(Triplet* imgs,
                  size_t size_imgs,
                  Haar* haar,
                  size_t size_haar)
{

  Caracteristique c;
  c.error = 2;
  c.margin = 0;
  size_t min = 0;


  for (size_t i = 0; i < size_haar; ++i)
  {
    for (size_t j = 0; j < size_imgs; ++j){
      compute_haar_sum(imgs[j].img, haar + i);
      imgs[j].sum = haar[i].sum;
    }

    //quickSort(imgs, 0, size_imgs - 1); // ATTENTION APPEL ADABOOST
    quickSort(imgs, (imgs + size_imgs));

    Caracteristique tmp = find_Decision_Stump(imgs, size_imgs);
    if (tmp.error < c.error || (tmp.error == c.error && tmp.margin > c.margin)) // ATTENTION VERIFIER WEIGHTED ERROR = caracteristique.error !!!!
    {
// Caracteristique = (threshold, toggle, error, margin)
      c.error = tmp.error;
      c.margin = tmp.margin;
      c.toggle = tmp.toggle;
      c.threshold = tmp.threshold;
      haar[i].error = tmp.error;
      haar[i].margin = tmp.margin;
      haar[i].polarity = tmp.toggle;
      haar[i].threshold = tmp.threshold;
      min = i;
    }
  }
  return min;
}


Model adaboost(Triplet* imgs, size_t size_imgs, int T)
{
  Model model;

  model.coefs = calloc(162336, sizeof(float));
  model.haars = malloc(sizeof(Haar)  * 162336);

  write_model(&model, "model.farce");

  size_t size_haar;
  Haar* haar = compute_haar_features(imgs->img, &size_haar);

  warnx("size %zu", size_haar);

  for (int t = 0; t < T; ++t)
  {
    write_model(&model, "modele.frc");

    size_t best = Best_stump(imgs,
                             size_imgs,
                             haar,
                             size_haar);

    warnx("%zu", best);
    assert(best > 0 && best < 162336);

    model.haars[best] = haar[best];

    print_Haar(model.haars[best]);

    float error = haar[best].error; // ATTENTION VERIFIER WEIGHTED ERROR = caracteristique.error !!!!

    if (error == 0 && t == 1)
    {
      for (int i = 0; i < 162336; ++i)
      {
        model.coefs[i] = 0;
      }
      model.coefs[best] = 1;
      return model;
    }
    else
    {
      assert(model.coefs[best] = (float)((float)
                                        ((float)1
                                         /
                                         (float)2) *
                                        log((float)((float)1 - error)/error)));

      for (Triplet* i = imgs; i < imgs + size_imgs; ++i)
      {

        //warnx("def poids img n°%zu\n", i - imgs);

        compute_haar_sum(i->img, haar + t);

        warnx("img%d : %f ->", i - imgs,  i->weight);

        assert(i->weight != INFINITY && i->weight != -INFINITY);
        assert(i->weight = (float)i->weight/2.0 *
          ((is_present(haar[t]) == i->is_a_face)?
           (float)((float)1/((float)1 - error)):
           (float)((float)1/((float)error))));


        if (i->weight != (float)((float)1/(float)size_imgs))
        {
          warnx("%f", i->weight);
        }
if (i->weight == INFINITY || i->weight == -INFINITY) {
  warnx("error : %f, face? : %d, present? : %d", error, i->is_a_face, is_present(haar[t]));
}
      }
    }
  }
  return model;
}

// Quick sort Sim:
Triplet* choose_pivot(Triplet *begin, Triplet *end){
  Triplet* mid = (begin + (end - begin)/2);
  if(begin->sum > mid->sum){
    if(mid->sum > end->sum)
      return mid;
    else if(begin->sum > end->sum)
      return end;
    else
      return begin;
  }
  else{
    if(begin->sum > end->sum)
      return begin;
    else if(mid->sum > end->sum)
      return end;
    else
      return mid;
  }
}

void swap(Triplet* a, Triplet* b){
  Triplet c = *b;
  *b = *a;
  *a = c;
}

Triplet* partition(Triplet *begin, Triplet *end, Triplet *pivot){
  Triplet pval = *(pivot);
  swap(pivot, end-1);
  pivot = begin;
  for (Triplet* i = begin; i < end-1; i++) {
    if (i->sum < pval.sum) {
      swap(pivot, i);
      pivot++;
    }
  }
  swap(pivot, end-1);
  return pivot;
}

void quickSort(Triplet *begin, Triplet *end){
  if (end - begin > 1) {
    Triplet* pivot = choose_pivot(begin, end-1);
    pivot = partition(begin, end, pivot);
    quickSort(begin, pivot);
    quickSort(pivot + 1, end);
  }
}
