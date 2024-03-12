void initjoueur(){
posSprit.x=0;
posSprite.y=0;
posSprite.w=0;
posSprit.h=0;
}

void animerjoueur(){
if (posSprit.x=largeurSprite -posSprite.w){
posSprite.x=0;
}
else posSprite.x=posSprite.x + posSprite.w ;
posSprite.y=direction*posSprite.h;
}
void afficherjoueur(){



/*void initPerso(Personne *p){ int o=0; 
char names[2][2][30]={{"./perso/chraity-IDLE.png","./perso/chraity_run.png"},{"./perso/fulll_screen/IDLE.png","./perso/fulll_screen/RUNNING.png"}};
 p->nbr_frames[0]=4;
 p->image[0].img=IMG_Load(names[o][0]);
 p->image[0].pos2.x=0; 
p->image[0].pos2.y=0;
 p->image[0].pos2.w=p->image[0].img->w/4; 
p->image[0].pos2.h=p->image[0].img->h/4-4; 
p->image[0].pos1.x=1000 //100;
 p->image[0].pos1.y=200;
//300;
 p->image[1].img=IMG_Load(names[o][1]);
 p->image[1].pos2.x=0;
 p->image[1].pos2.y=0;
 p->image[1].pos2.w=p->image[1].img->w/8;
 p->image[1].pos2.h=p->image[1].img->h/4;
 p->image[1].pos1.x=1000;
//100; 
p->image[1].pos1.y=200;
//300;
 p->nbr_frames[1]=8;
p->speed=0.001;
 p->initlevel=0;
 p->caught=0; 
p->hitTime=0;
 p->invinWindow=1500;
 p->invin=0;
 p->hit=0; 
p->staminaBar=IMG_Load("omar_backgounf/stamina_0000_Layer-1.png"); 
p->staminaImg=IMG_Load("omar_backgounf/stamina_0001_Layer-2.png"); 
p->dangerLevelStaBar=IMG_Load("omar_backgounf/dangerlevel_0000_Layer-1.png");
 p->dangerLevelStaImg=IMG_Load("omar_backgounf/dangerlevel_0001_Layer-2.png");
 p->stamina=13000; 
p->staminapos2.x=0;
 p->staminapos2.y=0;
 p->staminapos2.w=170;
 p->staminapos2.h=29; 
p->dangerLevelStapos2.x=0;
 p->dangerLevelStapos2.y=0;
 p->dangerLevelStapos2.w=170;
 p->dangerLevelStapos2.h=29;
p->staminapos1.x=120;
 p->staminapos1.y=515; 
p->coke=0; p->tea=0;
 p->consumeTime=0;
 p->consuming=0;
 p->recovery=0;
 p->caughtTime=0;
 p->score=0;
 p->image[1].pos1.w=p->image[0].img->w/4;
 p->image[1].pos1.h=p->image[0].img->h/4;
 p->fish=0; }

void initPerso_2(Personne *p){ p->nbr_frames[0]=4;
 p->image[0].img=IMG_Load("./perso/omarrcara.png");
 p->image[0].pos2.x=0;
 p->image[0].pos2.y=0;
 p->image[0].pos2.w=p->image[0].img->w/4;
 p->image[0].pos2.h=p->image[0].img->h/4; p->image[0].pos1.x=100; p->image[0].pos1.y=300;
 p->image[1].img=IMG_Load("./perso/omaraaa (1).png");
 p->image[1].pos2.x=0; 
p->image[1].pos2.y=0;
 p->image[1].pos2.w=p->image[1].img->w/8;
 p->image[1].pos2.h=p->image[1].img->h/4; 
p->image[1].pos1.x=100;
 p->image[1].pos1.y=300;
 p->nbr_frames[1]=8; 





}
void afficherPerso(Personne p, SDL_Surface * screen){ SDL_BlitSurface(p.image[p.where].img,&p.image[p.where].pos2,screen,&p.image[p.where].pos1); } void animerPerso (Personne* p){ p->image[p->where].pos2.x+=p->image[p->where].pos2.w ; p->image[p->where].pos2.y=(p->image[p->where].img->h/4)*(p->derec-1); if(p->image[p->where].pos2.x+p->image[p->where].pos2.w>=p->image[p->where].img->w) p->image[p->where].pos2.x=0; } void deplacerPerso (Personne *p,int dt){ p->distance=0.5*(p->acc)*dt*dt+p->speed*dt; if(p->acc>0){ switch (p->derec) { case 1: p->image[p->where].pos1.y+=p->distance; break; case 2: p->image[p->where].pos1.y-=p->distance; break; case 3: p->image[p->where].pos1.x+=p->distance; break; case 4: p->image[p->where].pos1.x-=p->distance; break; } } if(p->where) p->image[0].pos1

void saut (Personne* p){ p->i+=10; p->image[p->where].pos1.y=0.04*(p->i)*(p->i)-100+p->y; if(p->derec==3) p->image[p->where].pos1.x+=6; else if(p->derec==4) p->image[p->where].pos1.x-=6; if(p->i>=50) {p->still_in=0;p->acc=0;} }






int collisionPP_persone(Personne p, SDL_Surface *Masque,int r,int g,int b) { SDL_Color color; int posX = p.image[p.where].pos1.x; int posY = p.image[p.where].pos1.y; int posX1 = posX + p.image[p.where].img->w / p.nbr_frames[p.where]; int posY1 = posY + p.image[p.where].img->h / 4; if (p.derec == 3 || p.derec == 4) { for (int i = posY1-30; i <= posY1-10; i++) {
 // Right 
color = GetPixel(Masque, posX1+p.bk_pos2.x, i + p.bk_pos2.y); 
if (color.r == r && color.g == g && color.b == b && p.derec == 3) return 1;
 // Left 
color = GetPixel(Masque, posX+p.bk_pos2.x, i + p.bk_pos2.y); if (color.r == r && color.g == g && color.b == b && p.derec == 4) return 1; } } else { for (int i = posX+10; i <= posX1-10; i++) { 
// TOP
 color = GetPixel(Masque, i + p.bk_pos2.x, posY1 + p.bk_pos2.y - 50);



void verticalJump2(Personne *p) { static int y,up=1; if(!p->vj) {y=p->image[1].pos1.y;up=1;} else { if(up&&p->image[1].pos1.y>y-100) p->image[1].pos1.y-=4; else up=0; if(!up&&p->image[1].pos1.y<y) p->image[1].pos1.y+=4; if(p->image[1].pos1.y>=y) {p->vj=0;p->image[1].pos1.y=y;} } }






void verticalJump(Personne *p) { static int y,up=1; if(!p->vj) {y=p->image[1].pos1.y;up=1;} else { if(up&&p->image[1].pos1.y>y-100) p->image[1].pos1.y-=4; else up=0; if(!up&&p->image[1].pos1.y<y) p->image[1].pos1.y+=4; if(p->image[1].pos1.y>=y) {p->vj=0;p->image[1].pos1.y=y;} } }


*/

