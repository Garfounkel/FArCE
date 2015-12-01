// Caracteristique = (threshold, toggle, error, margin)


// algorithme 4

Caracteristique find_Decision_Stump(Triplet* train_exp, size_t n, Haar haar) {

  int t = 0; // Treshold
  for (size_t i = 0; i < n; i++) {
    if (train_exp[i].sum < t)
      t = train_exp[i].sum;
  }

  int M = 0; // Margin
  int e = 2; // Error

  //Sum up the weights of the positive (resp. negative) examples whose f-th feature is bigger than the present threshold
  int WpSup = 0, WnSup = 0 WpInf = 0, WnInf = 0;
  for (size_t i = 0; i < n; i++) {

    if (train_exp[i].is_a_face) {
      if (train_exp[i].sum > t)
        WpSup += train_exp[i].sum;
      else
        WnSup += train_exp[i].sum;
    }
    else {
      if (train_exp[i].sum > t)
        WpInf += train_exp[i].sum;
      else
        WnInf += train_exp[i].sum;
    }
  }

  size_t j = 0;
}
