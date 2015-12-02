#ifndef ADABOOST_IPOL_H_
# define ADABOOST_IPOL_H_

typedef struct Caracteristique Caracteristique;
struct Caracteristique{
    int treshold;
    int toggle;
    int error;
    int margin;
};


#endif /* !ADABOOST_IPOL_H_ */
