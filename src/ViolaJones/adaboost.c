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



// Adaboost pseudo-code:

Model adaboost(Triplet* imgs, size_t len_imgs)
{
  Model model;
  model.coefs = malloc(sizeof(float) * 200000);
  model.haars = malloc(sizeof(Haar) * 200000);

  size_t size_features;
  Haar* features = compute_haar_features(imgs->img, &size_features);
  long threshold = 10;

  while (1) {

    int min = 0;
    Haar haar_min;
    double errormin = 1;

    for (size_t f = 0; f < size_features; ++f)
    {
      double error = 0;

      for (Triplet* i = imgs; i < imgs + len_imgs; ++i)
      {
        compute_haar_sum(i->img, &features[f]);
        error +=
          i->weight *
          i->is_a_face *
          is_present(features[f], threshold);
      }

      if (error <= errormin) {
        errormin = error;
        haar_min = features[f];
        min = f;
      }

    }

    if (errormin >= 0.5) {
      return model;
    }

    model.coefs[min] = 1/2*log((1 - errormin)/errormin);
    model.haars[min] = haar_min;

    for (Triplet* i = imgs; i < imgs + len_imgs; ++i)
    {
      i->weight =
        i->weight *

        exp(
          -model.coefs[min] *
          i->is_a_face *
          is_present(haar_min, threshold))

        /

        (2*sqrt(errormin*(1 - errormin)));
    }

  }
}
