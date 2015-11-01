# include"boosting.h"

//error 1/10000000

int adaboost(int nb_img,char**list_img,)
{//int visage [-1,1]
float error=1/(nb_img*100);//init error rate to avoid div by 0
float weight=1/2*log((1-error)/error), pond=1/nb_img;
int h=1;//resultat de haar[1,-1] -1 =faux 1 =vrai
int nb_error=1;nbr //d'erreur
int i=0;
 for (;(i<nb_img) &&(error<0.5);i++)
  {    //h=parcour de haar
    if(/*visage */ != h )
      {
        
        error+=pond*nb_error;
        if(error>1/2){break;}
        nb_error++;
        weight=1/2*log((1-error)/error);
        
       }
      pond=(pond*exp(-weight*h*/*visage*/)))/(2*sqrt(error(1-error)));
   }
return i;//savoir ou on s'est arrete 
}
