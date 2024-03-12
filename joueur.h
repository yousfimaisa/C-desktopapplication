// avec methode de spritesheet 
typedefstruct{
SDL_Surface *sprite;
int direction; // 0:droite 1: gauche
SDL_Rect postScreen;
SDL_Rect popSprite ;

}animation_joueur; 





/*
typedef struct{
SDL_Rect pos1,pos2;
SDL_Surface *img;
}ima;
typedef struct {
SDL_Rect postxt;
SDL_Surface *windtxt ;
SDL_Color col ;
}TEXT;

typedef struct {
ima image[2];
int derec,where,nbr_frames[2],still_in , still_in2 ,i,y,scrolling_on , coll_derection,distance;
float acc,speed;
SDL_Rect bk_pos2;
int intlevel;
int vj;
int panana;
int score;
int invinwindow;
int hitTime;
int invin;
int stamina;
SDL_Surface *staminaBar ,*staminaImg , *dangerLevelStaBar , *dangerLevelStaImg;
SDL_Rect staminapos2, dangerLevelStapos2,staminapos1;
int hit;
int coke,tea;
int recovery;
int consumeTime;
int consuming ;
Mix_Chunk *drinkingTea ,*drinkingCoke ,*openTuna;
int caughtTime;
int fish;
}personne;

void initperso(personne *p);
void afficherperso(personne p , SDL_Surface * screen );
void deplacerperso(personne *p , int dt);
void animerperso(personne *p);
void saut(personne *p);

int collisionpp_persone(personne p,SDL_Surface *Masque , int r, int g, int b);
void initperso_2(personne *p);
void verticalJump(personne *p);
void verticalJump(personne *p); */
