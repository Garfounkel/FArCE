// Caracteristique = (threshold, toggle, error, margin)

#include "adaboost.h"

// algorithme 4

Caracteristique find_Decision_Stump(Triplet* train_exp, size_t n) {

  int t = 0; // Treshold
  for (size_t i = 0; i < n; i++) {
    if (train_exp[i].sum < t)
      t = train_exp[i].sum;
  }

  int M = 0; // Margin
  int error = 2; // Error

  //Sum up the weights of the positive (resp. negative) examples whose f-th feature is bigger than the present threshold
  float WpSup = 0, WnSup = 0, WpInf = 0, WnInf = 0;
  for (size_t i = 0; i < n; i++) {

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
  }

  size_t j = 0;
  int tbar = t;
  int Mbar = M;
  int T;

  while (1) {
    int errorp = WpInf + WnSup;
    int errorn = WpSup + WnInf;
    T = errorp > errorn ? 1 : -1;

    int errorbar;
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

    if (errorbar < error || (errorbar = error && Mbar > M))
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
        WpSup += train_exp[j].weight;
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
        if (train_exp[i].sum < t)
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
  int min;


  for (size_t i = 0; i < size_haar; ++i)
  {
    for (size_t j = 0; j < size_imgs; ++j){
      compute_haar_sum(imgs[j].img, haar + i);
      imgs[j].sum = haar[i].sum;
    }

    sort(imgs); // ATTENTION APPEL ADABOOST

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


Model adaboost(Triplet* imgs,
               size_t size_imgs,
               Haar* haar,
               size_t size_haar,
               int T)
{
  Model model;

  model.coefs = calloc(162336, sizeof(float));
  model.haars = malloc(sizeof(Haar)  * 162336);

  write_model(&model, "model.farce");


  for (int t = 0; t < T; ++t)
  {
    size_t best = Best_stump(imgs,
                             size_imgs,
                             haar,
                             size_haar);

    model.haars[best] = haar[best];

    float error = haar[best].error; // ATTENTION VERIFIER WEIGHTED ERROR = caracteristique.error !!!!

    if (error == 0 && t == 1)
    {
      for (int i = 0; i < 162336; ++i)
      {
        model.coefs[i] = 0;
      }
      model.coefs[best] = 1;
      return model; // INCORRECT
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

        assert(i->weight = (float)i->weight/2 *
          ((is_present(haar[t]) == i->is_a_face)?
           (float)((float)1/((float)1 - error)):
           (float)((float)1/((float)error))));

        if (i->weight != (float)1/size_imgs)
        {
          warnx("%f", i->weight);
        }
      }
    }
  }
  return model;
}
