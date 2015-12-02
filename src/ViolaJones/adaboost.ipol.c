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
}
