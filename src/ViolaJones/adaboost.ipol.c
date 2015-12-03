// Caracteristique = (threshold, toggle, error, margin)


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
  int mbar = m;

  while (1) {
    int errorp = WpInf + WnSup;
    int errorn = WpSup + WnInf;
    int T = errorp > errorn ? 1 : -1;

    int errorbar;
    int Tbar;

    if (errorp < errorm)
    {
      errorbar = errorp;
      Tbar = 1;
    }
    else
    {
      errorbar = errorm;
      Tbar = -1;
    }

    if (errorbar < error || (errorbar = error && mbar > m))
    {
      error = errorbar;
      t = tbar;
      m = mbar;
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
      mbar = 0;
    }
    else {
      tbar = (train_exp[j].sum + train_exp[j + 1].sum)/2;
      mbar = train_exp[j + 1].sum - train_exp[j].sum;
    }
  }
  return dzijdzidjzdijdzijdzj
}



size_t Best_stump(Triplet* imgs,
                           size_t size_imgs,
                           Haar* haar,
                           size_t size_haar)
{

  Caracteristique c;
  c.error = 2;
  c.margin = 0;

  for (int i = 0; i < size_haar; ++i)
  {
    for (int j = 0; j < size_imgs; ++j)
      Triplet[j].sum = compute_haar();

    sort(Triplet);

    Caracteristique tmp = find_Decision_Stump(imgs, size_imgs);
    if (tmp.error < c.error || tmp.margin > c.margin) // ATTENTION VERIFIER WEIGHTED ERROR = caracteristique.error !!!!
    {
// Caracteristique = (threshold, toggle, error, margin)
      c.error = tmp.error;
      c.margin = tmp.margin;
      c.toggle = tmp.toggle;
      c.threshold = tmp.threshold;
      Haar[i].error = tmp.error;
      Haar[i].margin = tmp.margin;
      Haar[i].polarity = tmp.toggle;
      Haar[i].threshold = tmp.threshold;
      min = i;
    }
  }
  return i;
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
    size_t best = Best_stump(Triplet* imgs,
                                   size_t size_imgs,
                                   Haar* haar,
                                   size_t size_haar);

    model.haars[best] = haar[best];

    error = c.error; // ATTENTION VERIFIER WEIGHTED ERROR = caracteristique.error !!!!

    if (error == 0 && t == 1)
    {
      return c; // INCORRECT
    }
    else
    {
      assert(model.coefs[min] = (float)((float)
                                        ((float)1
                                         /
                                         (float)2) *
                                        log((float)((float)1 - error)/error)));

      for (Triplet* i = imgs; i < imgs + len_imgs; ++i)
      {

        //warnx("def poids img n°%zu\n", i - imgs);

        assert(i->weight = (float)i->weight/2 *
          ((is_present(Haar[t],i) == i->is_a_face)?
           (float)((float)1/((float)1 - error)):
           (float)((float)1/((float)error))));

        if (i->weight != (float)1/len_imgs)
        {
          warnx("%f", i->weight);
        }
      }
    }
  }
  return Model;
}
