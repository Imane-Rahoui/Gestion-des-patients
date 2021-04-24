#include "Coronavirus.h"
void majmini(char**c) // pour avoir la 1 ere lettre en majuscule et la suite en minisucle
{
    int i,size=strlen(c[0]);
    c[0][0]=toupper(c[0][0]);
    for(i=1; i<size; i++)
        c[0][i]=tolower(c[0][i]);
}
char* sv_alpha()
{
    char n[60],*ch;
    int size,flag,i,rep=1;
    fflush(stdin);
    gets(n);
    while(rep==1)
    {
        flag=1; //pour pouvoir faire la verification
        rep=0; //pour sortir de la bcl si la chaine contient que des lettres
        n[59]='\0'; //sécurité
        size=strlen(n);
        for(i=0; i<size && flag==1; i++) //si flag==0 c est que c'est pas que des lettres donc pas la peine de continuer la recherche
        {
            if( isalpha(n[i])==0 && n[i]!=' ')  //soit j'ai rencontré un chiffre ou cara special sauf l espace c'est accepté
                flag=0;
        }
        if(flag==0 || n[0]=='\0'|| n[0]==' ') //si je fait un 'entrer' sans saisir ou je fais rentrer un space au debut c pas accepté
        {
            printf("Error! Veuillez reessayer : \n");
            gets(n);
            rep=1; // pour verifier la nouvelle chaine si il y a que des lettres ou pas
        }
    }
    ch=malloc((size+1)*sizeof(char));
    strcpy(ch,n);
    majmini(&ch);
    return ch;
}
int sv_number(int inf,int sup)
{
    char c[5];
    int j=0,i,flag=0;
    fflush(stdin);
    gets(c);
    c[4]='\0';//securité
    for(i=0; c[i]!='\0' && flag==0; i++)
    {
        if(isdigit(c[i])==0) //si je rencontre une lettre ou cara special je sors directe
            flag=1;

        else
            j=10*j+c[i]-'0';
    }
    while(flag==1 || j<inf || j>sup)
    {
        j=0;
        flag=0;
        printf("Error! Veuillez reessayer : ");
        fflush(stdin);
        gets(c);
        c[4]='\0';//securité
        for(i=0; c[i]!='\0' && flag==0; i++)
        {
            if(isdigit(c[i])==0)
                flag=1;
            else
                j=10*j+c[i]-'0';
        }
    }
    return j;
}
liste_maladies* ajouter_maladie(liste_maladies*l,char*maladie,int flag) //flag=0 il faut faire une reservation en memoire sinon nn deja faite il suffit de chainer
{
    liste_maladies*tmp=malloc(sizeof(liste_maladies));
    /* j ai pas ajouter le test de si l est NULL je ss que ma liste sera tjrs pleine */
    int size,i;
    if(flag==0)
    {
        size=strlen(maladie);
        tmp->maladie=malloc((size+1)*sizeof(char)); // le +1 pour stocker le '\0'
        majmini(&maladie);
        strcpy(tmp->maladie,maladie);
    }
    else
    {
        tmp->maladie=maladie;
    }
    tmp->next=l; // l'insertion de la liste se fait toujours au debut
    return tmp;
}
int afficher_liste_maladies(liste_maladies*l)
{
    int i=0;
    printf("La liste des maladies : \n");
    while(l!=NULL)  // tant que la liste est pleine je vais tjrs afficher le contenue de l->maladie
    {
        printf("%d - ",i++);
        puts(l->maladie);
        l=l->next;
    }
    return i; //je vais avoir besoin du nbr des maladies enregistrées au nv de l ajout soit d une prs ou un pat
}
bool verifier_email(char*e)
{
    int i,j,k,l;
    char tmp[40]; // 30 juste pr etre sure puisque les suffixes et les domaines ne depassent pas 8 cara
    if(isalpha(e[0])!=0) //je doit commencer par une lettre
    {
        for(i=0; e[i]!='\0' && e[i]!='@'; i++)
        {
            if(isalnum(e[i])==0 && (e[i]!='-' && e[i]!='_' && e[i]!='.'))
                return False; //un email ne peut contenir que des lettres des chiffres et des (-_.)
        } //tant que je suis pas arrivée au \0 ou @ j'ai pas le droit de sortir
        if(i>5 && e[i]=='@') //  e[i]=='@' condition pas obligatoire
            // l etiquette doit contenir au moins 6 cara
        {
            for(j=i+1,k=0; e[j]!='\0' && e[j]!='.'; j++,k++) //tant que je suis pas arrivée au \0 ou . je sors pas
                tmp[k]=e[j]; // je copie le domaine sur tmp pour le comparer vc les autres
            tmp[k]='\0';
            for(i=0,l=1; tmp[0]!='\0' && l!=0 && i<8 ; i++)
                // le tmp[0]!='\0' pcq si on ecrit imaaaan@.com tmp va etre une chaine vide ça sert à rien de comparer vc une chaine vide
                l=strcmp(tmp,domaines[i]);
            if(l==0 && e[j+1]!='\0')
//                 si tmp=domaines[i] la fct strcmp va retourner le NULL donc je peut passer pour verifier les suffixes sinon c'est pas la peine
            {
//               stockage du suffixe dans le tmp pour comparer par la suite
                for(j=j+1,k=0; e[j]!='\0'; j++,k++)
                    tmp[k]=e[j];
                tmp[k]='\0';
                for(i=0,l=1; i<4 && l!=0; i++)
                    l=strcmp(tmp,sufixes[i]);
                if(l==0)
//                     et à la fin si on arrive à ce if et que les conditions sont verifiées donc l'email est valide
                    return True;
            }
        }
    }
    return False;
}
bool verifier_ville(char*v)
{
    int i,flag;
    for(i=0,flag=1; i<67 && flag!=0 ; i++)
// soit je vais sortir pcq i==67 ou flag ==0
        flag=stricmp(v,villes[i]);
    if(flag==0)
        //je vais sortir mn la bcl vc l'indice de la ville identique +1 c pour ça j ai mis le i-1
        //je retoune l'indice de la ville identique il va me servir apres pr ecrire joliment
        return i-1;
    return -1;
}
int* sv_tele(void)
{
    int i,*t;
    char cc;
    t=malloc(10*sizeof(int));
    printf("Veuillez saisir le n° de tele/fix : ");
    t[0]=0; // obligatoirement le premier chiffre c'est 0
    printf("%d",t[0]);
    i=1; // le 0 est stocké et affiché on passe au 2 eme chiffre
    do
    {
        cc = getch(); //lire le caractere sans un echo à l ecran
        if(cc == '5' || cc== '6' || cc== '7')
            // si c'est validée on affiche et on stocke dns le tab sinon on refait jusqu'à qu'on recoit le resultat qu'on cherche
        {
            printf("%c", cc);
            t[1]=(cc-'0');
            i++;
        }
    }
    while(i==1);
    do
    {
        cc = getch();
        // cette fois la condition est que i soit inf à 10 et le cara saisie est un chiffre de 0 à 9
        if(i<10  && (cc >= '0' && cc<= '9' ))
        {
            // si i==2 pas la peine de caché le nombre qui la precede sinon oui pour des raisons de securité
            if(i!=2)
            {
                printf("\b");
                printf("*");
            }
            printf("%c", cc);
            t[i]=(cc-'0');
            i++;
        }
    }
    while(i<10); //on arrete le processus si on arrive à 10 chiffres
    printf("\n");
    return t;
}
etats* ajouter_etat(etats*l,char*etat)
{
    etats*tmp;
    //la meme chose que la fct d ajout des maladies pour le test du NULL
    int size=strlen(etat),i;
    tmp=malloc(sizeof(etats));
    tmp->next=l; // l'insertion de la liste se fait toujours au debut
    tmp->etat=malloc((size+1)*sizeof(char)); // le +1 pour stocker le '\0'
    strcpy(tmp->etat,etat);
    return tmp;
}
void afficher_liste_etats(etats*l,int flag) //au nv d ajout du patient je doit pas afficher l etat mort et gueri
{
    int i=0;
    if(flag!=0)
        printf("Les etats : \n");
    while(l!=NULL)  // tant que la liste est pleine je vais tjrs afficher le contenue de l->etat
    {
        printf("%d - ",i++);
        puts(l->etat);
        l=l->next;
        if(flag==0 && i==4)
            l=NULL;

    }
}
bool verifier_date(date*d)
{
    if(d->j>=1 && d->m>=1 && d->m<=12)
    {
        if(((d->m==1 ||d->m==3 || d->m==5 ||d->m==7 || d->m==8 || d->m==10 || d->m==12) && d->j<=31 )|| ((d->m==4 ||d->m==6 || d->m==9 ||d->m==11) && d->j<31) || (d->m==2 && d->j<=29))
            return True;
    }
    return False;
}
bool compa_dates(date dd,date df)
{
    //logiquement la date de fin ne peut qu etre sup à celle du debut
    if(dd.m < df.m )
        return True;
    else if(dd.m==df.m)
    {
        if(dd.j < df.j )
            return True;
    }
    return False;
}
char* sv_CIN()
{
    char n[9],*CIN;
    int i,flag=0,j=1;
    while(flag!=8)
    {
        fflush(stdin);
        printf("Veuillez saisir le CIN : ");
        gets(n);
        n[8]='\0';
        flag=strlen(n); //si c composé de 8 cara là je teste si les 2 premiers sont des lettres et les autres des chiffres
        if(flag==8)
        {
            if(isalpha(n[0])!=0 && isalpha(n[1])!=0)
            {
                for(i=2; i<8 && flag!=0; i++)
                {
                    if(isdigit(n[i])==0 )
                        flag=0;
                }
            }
            else
                flag=0;
        }
    }
    CIN=malloc(9*sizeof(char));
    n[0]=toupper(n[0]);
    n[1]=toupper(n[1]);
    strcpy(CIN,n);
    return CIN;
}
adresse* sv_adresse(void)
{
    char cc;
    int i;
    adresse*ad=malloc(sizeof(adresse));
    printf("L'addresse:\n");
    printf("Veuillez saisir la ville : ");
    ad->ville=sv_alpha();
    i=verifier_ville(ad->ville);
    while(i==-1)
    {
        printf("Error! Veuillez reessayer :");
        free(ad->ville);
        ad->ville=sv_alpha();
        i=verifier_ville(ad->ville);
    }
    printf("Veuillez saisir le quartier : ");
    ad->quartier=sv_alpha();
    printf("Veuillez saisir la rue : ");
    ad->rue=sv_alpha();
    ad->code=0;
    i=0;
    printf("Veuillez saisir le code postal: ");
    do
    {
        cc = getch();
        //un code postal se compose de 5 chiffre
        if(i<5  && (cc >= '0' && cc<= '9' ))
        {
            printf("%c", cc);
            ad->code=10*ad->code+(cc-'0');
            i++;
        }
    }
    while(i<5);
    printf("\n");
    return ad;
}
hopital* ajouter_hopital(hopital*hp)
{
    hopital*h=malloc(sizeof(hopital));
    printf("Veuillez saisir le nom de l'hopital : ");
    h->nom=sv_alpha();
    h->ad=sv_adresse();
    h->fix=sv_tele();
    printf("Veuillez saisir le nombre des lits dans la réanimation : ");
    h->lits_rea=sv_number(0,1000);
    printf("Veuillez saisir le nombre des lits ailleurs : ");
    h->lits_norm=sv_number(0,1000);
    printf("Veuillez saisir le nombre des salles pour les besoins spécifiques : ");
    h->salles_speci=sv_number(0,1000);
    printf("Veuillez saisir le nombre des médecins spécialisés : ");
    h->nbr_medecins=sv_number(0,1000);
    printf("Veuillez saisir le nombre des paramedicaux : ");
    h->nbr_paramedi=sv_number(0,1000);
    h->next=hp;
    return h;
}
hopital* modifier_hopital(hopital*h)
{
    int i;
    char n[20];
    hopital*tmp=h;
    if(h==NULL)
    {
        printf("Aucun hopital enregistré ! \n");
        printf("Si vous voulez l'enregistrer veuillez tappez 1 sinon tappez 0 : ");
        i=sv_number(0,1);
        if(i==1)
            return ajouter_hopital(h);
    }
    else
    {
        fflush(stdin);
        printf("Veuillez saisir le nom de l'hopital que vous cherchez : ");
        gets(n);
        n[19]='\0';
        while(tmp!=NULL && i!=0)
        {
            i=stricmp(tmp->nom,n);
            if(i!=0)
                tmp=tmp->next;
        }
        if(i!=0)
        {
            printf("Aucun hopital avec ce nom ! \n");
            return h;
        }
        else
        {
            do
            {
                printf("Tappez le nombre correspondant à ce que vous voullez modifier :\n");
                printf("1-Le nom de l'hopital: \n");
                printf("2-L'adresse de l'hopital: \n");
                printf("3-Le n° du fix de l'hopital: \n");
                printf("4-Le nombre de lits de reanimation de l'hopital: \n");
                printf("5-Le nombre des lits ailleurs de l'hopital: \n");
                printf("6-Le nombre des salles pour les besoins spécifiques de l'hopital: \n");
                printf("7-Le nombre des médecins spécialisés de l'hopital: \n");
                printf("8-Le nombre des paramedicaux de l'hopital: \n");
                printf("9-Quitter: \n");
                i=sv_number(1,9);
                switch(i)
                {
                case 1 :
                    free(tmp->nom);
                    printf("Veuillez saisir le nom de l'hopital : ");
                    tmp->nom=sv_alpha();
                    break;
                case 2 :
                    free(tmp->ad);
                    tmp->ad=sv_adresse();
                    break;
                case 3 :
                    free(tmp->fix);
                    tmp->fix=sv_tele();
                    break;
                case 4 :
                    printf("Veuillez saisir le nombre des lits dans la réanimation : ");
                    tmp->lits_rea=sv_number(0,10000);
                    break;
                case 5 :
                    printf("Veuillez saisir le nombre des lits ailleurs : ");
                    tmp->lits_norm=sv_number(0,10000);
                    break;
                case 6 :
                    printf("Veuillez saisir le nombre des salles pour les besoins spécifiques : ");
                    tmp->salles_speci=sv_number(0,1000);
                    break;
                case 7 :
                    printf("Veuillez saisir le nombre des médecins spécialisés : ");
                    tmp->nbr_medecins=sv_number(0,1000);
                    break;
                case 8 :
                    printf("Veuillez saisir le nombre des paramedicaux : ");
                    tmp->nbr_paramedi=sv_number(0,1000);
                    break;
                default:
                    textcolor(CYAN+BLINK);
                    cprintf("Modifications enregistrés \n");
                }
            }
            while(i>0 && i<9);
        }
    }
    return h;
}
void afficher_hopital(hopital*h,int flag) //si flag==0 j affiche qu un seul hopit sinon tt la liste
{
    int i=0;
    while(h!=NULL)
    {
        printf("\n");
        printf("Le nom : ");
        puts(h->nom);
        printf("L'adresse :\n");
        printf("La ville : ");
        puts(h->ad->ville);
        printf("Le quartier : ");
        puts(h->ad->quartier);
        printf("La rue : ");
        puts(h->ad->rue);
        printf("Le code postal : %ld \n",h->ad->code);
        printf("Le n° du Fix : ");
        for(i=0; i<10; i++)
            printf("%d",h->fix[i]);
        printf("\n");
        printf("Le nombre des lits dans la réanimation : %d \n",h->lits_rea);
        printf("Le nombre des lits ailleurs : %d\n",h->lits_norm);
        printf("Le nombre des salles pour les besoins spécifiques : %d \n",h->salles_speci);
        printf("Le nombre des médecins spécialisés : %d \n",h->nbr_medecins);
        printf("Veuillez saisir le nombre des paramedicaux : %d \n",h->nbr_paramedi);
        if(flag==0)
            h=NULL;
        else
            h=h->next;
    }
    if(flag!=0 && i==0)
        printf("Aucun hopital enregistré \n");
}
hotel* ajouter_hotel(hotel*ht,int flag)//si flag==0 j saisie que l adresse sinon tt
{
    hotel*h=malloc(sizeof(hotel));
    if(flag!=0)
    {
        printf("Veuillez saisir le nom de l'hotel : ");
        h->nom=sv_alpha();
        printf("Veuillez saisir le nombre des places disponibles : ");
        h->dispo=sv_number(0,10000);
        h->next=ht;
    }
    h->ad=sv_adresse();
    if(flag==0)
    {
        h->dispo=-6;
        return h;
    }
    h->fix=sv_tele();
    return h;
}
void afficher_hotel(hotel*h,int flag) //si flag==0 j affiche qu un seul hotel sinon tt la liste
{
    int i=0;
    while(h!=NULL)
    {
        printf("L'hotel : \n");
        printf("Le nom : ");
        puts(h->nom);
        printf("L'adresse :\n");
        printf("La ville : ");
        puts(h->ad->ville);
        printf("Le quartier : ");
        puts(h->ad->quartier);
        printf("La rue : ");
        puts(h->ad->rue);
        printf("Le code postal : %ld \n",h->ad->code);
        printf("Le n° du Fix : ");
        for(i=0; i<10; i++)
            printf("%d",h->fix[i]);
        printf("\n");
        printf("Le nombre des places disponibles : %d \n",h->dispo);
        if(flag==0)
            h=NULL;
        else
        {
            h=h->next;
            printf("\n");
        }
    }
    if(flag!=0 && i==0)
        printf("Aucun hotel enregistré \n");
}
hotel* modifier_hotel(hotel*h)
{
    int i,size;
    char n[20];
    hotel*tmp=h;
    if(h==NULL)
    {
        printf("Aucun hotel enregistré ! \n");
        printf("Si vous voulez l'enregistrer veuillez tappez 1 sinon tappez 0 : ");
        i=sv_number(0,1);
        if(i==1)
            return ajouter_hotel(h,1);
    }
    else
    {
        printf("Veuillez saisir le nom de l'hotel que vous cherchez : ");
        gets(n);
        n[19]='\0';
        while(tmp!=NULL && i!=0)
        {
            i=stricmp(tmp->nom,n);
            if(i!=0)
                tmp=tmp->next;
        }
        if(i!=0)
        {
            printf("Aucun hotel avec ce nom ! \n");
            return h;
        }
        do
        {
            printf("Tappez le nombre correspondant à ce que vous voullez modifier :\n");
            printf("1-Le nom de l'hotel: \n");
            printf("2-L'adresse de l'hotel: \n");
            printf("3-Le n° du fix de l'hotel: \n");
            printf("4-Le nombre des places disponibles : \n");
            printf("5-Quitter: \n");
            i=sv_number(1,5);
            switch(i)
            {
            case 1 :
                free(tmp->nom);
                printf("Veuillez saisir le nom de l'hotel : ");
                tmp->nom=sv_alpha();
                break;
            case 2 :
                free(tmp->ad);
                tmp->ad=sv_adresse();
                break;
            case 3 :
                free(tmp->fix);
                tmp->fix=sv_tele();
                break;
            case 4 :
                printf("Veuillez saisir le nombre des places disponibles : ");
                tmp->dispo=sv_number(0,10000);
                break;
            default:
                textcolor(CYAN+BLINK);
                cprintf("Modifications enregistrés \n");
            }
        }
        while(i>0 && i<5);
    }
    return h;
}
// C'est deux fonctions ms c'est juste que je les ai pas utikisé
//hopital* supp_hopital(hopital*h,char*n)
//{
//    hopital*aide=h,*tmp=h;
//    while(tmp!=NULL && stricmp(tmp->nom,n)!=0)
//    {
//        aide=tmp;
//        tmp=tmp->next;
//    }
//    if(tmp!=NULL && stricmp(tmp->nom,n)==0)
//    {
//        if(h==tmp)   // pour le cas de suppression au debut
//            h=h->next;
//        else         // pour le cas de suppression au milieu ou la fin
//         {
//             aide->next=tmp->next;
//             free(tmp->nom);
//             free(tmp->ad->ville);
//             free(tmp->ad->quartier);
//             free(tmp->ad->rue);
//             free(tmp->ad);
//             free(tmp->fix);
//             free(tmp);
//         }
//    }
//    return h;
//}
//hotel* supp_hotel(hotel*h,personne*p,char*n)
//{
//    hotel*aide=h,*tmp=h;
//    while(tmp!=NULL && stricmp(tmp->nom,n)!=0)
//    {
//        aide=tmp;
//        tmp=tmp->next;
//    }
//    if(tmp!=NULL && stricmp(tmp->nom,n)==0)
//    {
//        if(h==tmp)   // pour le cas de suppression au debut
//            h=h->next;
//        else         // pour le cas de suppression au milieu ou la fin
//        aide->next=tmp->next;
//        free(tmp->nom);
//        free(tmp->ad->ville);
//        free(tmp->ad->quartier);
//        free(tmp->ad->rue);
//        free(tmp->ad);
//        free(tmp->fix);
//        free(tmp);
//    }
//    while(p!=NULL)
//    {
//        if(p->hot->dispo!=-6 && stricmp(p->hot->nom,n)==0)
//        {
//        free(p->hot->nom);
//        free(p->hot->ad->ville);
//        free(p->hot->ad->quartier);
//        free(p->hot->ad->rue);
//        free(p->hot->ad);
//        free(p->hot->fix);
//        free(p->hot);
//        p->hot=NULL;
//        }
//        else
//        {
//        free(p->hot->ad->ville);
//        free(p->hot->ad->quartier);
//        free(p->hot->ad->rue);
//        free(p->hot->ad);
//        free(p->hot);
//        p->hot=NULL;
//        }
//    }
//    return h;
//}
void afficher_maladie(liste_maladies*l)
{
    if(l!=NULL)
        puts(l->maladie);
}
personne* ajouter_personne(personne*lp,liste_maladies**lm)
{
    personne*p=malloc(sizeof(personne));
    liste_maladies*ltmp;
    int flag,size,i,j,k,aide;
    char n[50],*m;
    p->CIN=sv_CIN();
    printf("Veuillez saisir le nom de la personne : ");
    p->nom=sv_alpha();
    printf("Veuillez saisir le prenom de la personne : ");
    p->prenom=sv_alpha();
    printf("Si C'est une femme veuillez tappez 1 sinon tappez 0 : ");
    flag=sv_number(0,1);
    if(flag==1)
    {
        p->sexe='F';
    }
    else
    {
        p->sexe='H';
    }
    printf("Veuillez saisir l'age : ");
    p->age=sv_number(1,150);
    p->hot=ajouter_hotel(NULL,0);
    p->tele=sv_tele();
    printf("Veuillez saisir l'email : ");
    fflush(stdin);
    gets(n);
    n[49]='\0';
    flag=verifier_email(n);
    while(flag!=True)
    {
        printf("Error! reessayez encore une fois : ");
        gets(n);
        n[49]='\0';
        flag=verifier_email(n);
    }
    size=strlen(n);
    p->email=malloc((size+1)*sizeof(char));
    strcpy(p->email,n);
    printf("Si la contamination est introduite veuillez tappez 1 sinon tappez 0 : ");
    flag=sv_number(0,1);
    if(flag==1)
    {
        p->contamination=True;
        printf("Veuillez saisir la prevenance : ");
        p->provenance=sv_alpha();
    }
    else
    {
        p->contamination=False;
        p->provenance=NULL;
    }
    k=afficher_liste_maladies(*lm);
    printf("Veuillez entrer le nombre de maladie dont cette personne souffre : ");
    aide=sv_number(0,k-1);
    p->maladies=NULL; //pour marquer la fin
    if(aide!=0)
    {
        p->maladies=malloc((aide+1)*sizeof(liste_maladies*));
        p->maladies[aide]=NULL; //pour marquer la fin
        for(i=0; i<aide; i++)
        {
            j=0;
            ltmp=*lm;
            printf("Tappez le nombre correspondant à la maladie dont cette parsonne souffre ( si vous voulez ajouter une autre tappez -1 ) : ");
            scanf("%d",&flag);
            while(flag<-1|| flag>k-1)
            {
                printf("Error! veuillez reessayer : ");
                scanf("%d",&flag);
            }
            size=1;
            while(ltmp!=NULL && flag!=-1 && size ==1)
            {
                if(flag==j)
                {
                    p->maladies[i]=ltmp;
                    size=2;
                }
                j++;
                ltmp=ltmp->next;
            }
            if(flag==-1)
            {
                printf("Veuillez saisir la maladie : ");
                m=sv_alpha();
                (*lm)=ajouter_maladie(*lm,m,1);
                p->maladies[i]=(*lm);
            }
        }
    }
    p->debut=malloc(sizeof(date));
    do
    {
        printf("Veuillez saisir la date du debut du quarantaine de la maniere suivante (jj/mm) : ");
        scanf("%hd /%hd",&p->debut->j,&p->debut->m);
    }
    while(verifier_date(p->debut)==0);
    p->fin=malloc(sizeof(date));
    do
    {
        printf("Veuillez saisir la date du fin du quarantaine de la maniere suivante (jj/mm) : ");
        scanf("%hd /%hd",&p->fin->j,&p->fin->m);
    }
    while(verifier_date(p->fin)==0 || compa_dates(*(p->debut),*(p->fin))==0);
    p->next=lp;
    return p;
}
void afficher_personne(personne*p,int flag) //siflag==0 donc j affiche une seule pers sinon tt la liste
{
    int i;
    if(p==NULL)
        printf("Aucune personne enregistrée \n");
    while(p!=NULL)
    {
        printf("Le CIN : ");
        puts(p->CIN);
        printf("Le nom : ");
        puts(p->nom);
        printf("Le prenom : ");
        puts(p->prenom);
        printf("Le sexe : ");
        printf("%c \n",p->sexe);
        printf("L'age : ");
        printf("%d \n",p->age);

        if(p->hot->dispo==-6)
        {
            printf("L'adresse :\n");
            printf("La ville : ");
            puts(p->hot->ad->ville);
            printf("Le quartier : ");
            puts(p->hot->ad->quartier);
            printf("La rue : ");
            puts(p->hot->ad->rue);
            printf("Le code postal : %ld \n",p->hot->ad->code);
        }
        else
        {
            afficher_hotel(p->hot,0);
        }
        printf("Le n° du Fix : ");
        for(i=0; i<10; i++)
            printf("%d",p->tele[i]);
        printf("\n");
        printf("L'email : ");
        puts(p->email);
        if(p->contamination==True)
        {
            printf("Contamination : introduite\n");
            printf("La provenance : ");
            puts(p->provenance);
        }
        else
            printf("Contamination : locale\n");
        printf("La date du debut du confinement : %hd/%hd\n",p->debut->j,p->debut->m);
        printf("La date du fin du confinement : %hd/%hd\n",p->fin->j,p->fin->m);
        printf("Les maladies chroniques : ");
        if(p->maladies==NULL)
            printf("Aucune\n");
        else
        {
            printf("\n");
            for(i=0; p->maladies[i]!=NULL; i++)
            {
                printf("%d - ",i);
                afficher_maladie(p->maladies[i]);
            }
        }
        p=p->next;
        if(flag==0)
            p=NULL;
    }
}
void afficher_patient(patient*p,int flag)
{
    int i;
    if(p==NULL)
        printf("Aucun patient enregistré \n");
    while(p!=NULL)
    {
        printf("Le CIN : ");
        puts(p->CIN);
        printf("Le nom : ");
        puts(p->nom);
        printf("Le prenom : ");
        puts(p->prenom);
        printf("Le sexe : ");
        printf("%c \n",p->sexe);
        printf("L'age : ");
        printf("%hd \n",p->age);
        printf("L'adresse :\n");
        printf("La ville : ");
        puts(p->ad->ville);
        printf("Le quartier : ");
        puts(p->ad->quartier);
        printf("La rue : ");
        puts(p->ad->rue);
        printf("Le code postal : %ld \n",p->ad->code);
        printf("Le n° du Fix : ");
        for(i=0; i<10; i++)
            printf("%d",p->tele[i]);
        printf("\n");
        printf("L'email : ");
        puts(p->email);
        if(p->contamination==True)
        {
            printf("Contamination : introduite\n");
        }
        else
            printf("Contamination : locale\n");
        if(p->maladies==NULL)
            printf("Maladie : Aucune\n");
        else
        {
            for(i=0; p->maladies[i]!=NULL; i++)
            {
                printf("%d - ",i);
                afficher_maladie(p->maladies[i]);
            }
        }
        if(p->hopit!=NULL)
            printf("l'Hopital : \n");
        afficher_hopital(p->hopit,0);
        printf("L'etat du patient : ");
        puts(p->etat->etat);
        printf("Le contact avec : ");
        if(p->prs==NULL)
            printf("Aucune personne \n");
        else
        {
            for(i=0; p->prs[i]!=NULL; i++)
            {
                printf("\n %d - ",i);
                afficher_personne(p->prs[i],0);
            }
        }
        if(flag==0)
            p=NULL;
        else
            p=p->next;
    }
}
patient* ajouter_patient(patient*lp,personne**pr,liste_maladies**lm,etats*l)
{
    patient*p=malloc(sizeof(patient));
    liste_maladies*ltmp;
    int flag,size,i,j,k,aide,help;
    char *n,m[30];
    p->hopit=NULL;
    p->CIN=sv_CIN();
    printf("Veuillez saisir le nom de la personne : ");
    p->nom=sv_alpha();
    printf("Veuillez saisir le prenom de la personne : ");
    p->prenom=sv_alpha();
    printf("Si C'est une femme veuillez tappez 1 sinon tappez 0 : ");
    flag=sv_number(0,1);
    if(flag==1)
    {
        p->sexe='F';
    }
    else
    {
        p->sexe='H';
    }
    printf("Veuillez saisir l'age : ");
    p->age=sv_number(1,150);
    p->ad=sv_adresse();
    p->tele=sv_tele();
    printf("Veuillez saisir l'email : ");
    fflush(stdin);
    gets(m);
    m[49]='\0';
    flag=verifier_email(m);
    while(flag!=True)
    {
        printf("Error! reessayez encore une fois : ");
        gets(m);
        m[49]='\0';
        flag=verifier_email(m);
    }
    size=strlen(m);
    p->email=malloc((size+1)*sizeof(char));
    strcpy(p->email,m);
    printf("Si la contamination est introduite veuillez tappez 1 sinon tappez 0 : ");
    flag=sv_number(0,1);
    if(flag==1)
        p->contamination=True;
    else
        p->contamination=False;
    k=afficher_liste_maladies(*lm);
    printf("Veuillez entrer le nombre de maladie dont cette personne souffre : ");
    aide=sv_number(0,k);
    p->maladies=NULL;
    if(aide!=0)
    {
        p->maladies=malloc((aide+1)*sizeof(liste_maladies*));
        p->maladies[aide]=NULL; //pour marquer la fin
        for(i=0; i<aide; i++)
        {
            j=0;
            ltmp=*lm;
            printf("Tappez le nombre correspondant à la maladie dont cette parsonne souffre ( si vous voulez ajouter une autre tappez -1 ) : ");
            scanf("%d",&flag);
            while(flag<-1|| flag>k-1)
            {
                printf("Error! veuillez reessayer : ");
                scanf("%d",&flag);
            }
            size=1;
            while(ltmp!=NULL && flag!=-1 && size ==1)
            {
                if(flag==j)
                {
                    p->maladies[i]=ltmp;
                    size=2;
                }
                j++;
                ltmp=ltmp->next;
            }
            if(flag==-1)
            {
                printf("Veuillez saisir la maladie : ");
                n=sv_alpha();
                (*lm)=ajouter_maladie(*lm,n,1);
                p->maladies[i]=(*lm);
            }
        }
    }
    afficher_liste_etats(l,0);
    printf("Veuillez tappez le nombre correspondant à l'etat du patient : ");
    flag=sv_number(0,3);
    size=1;
    j=0;
    while(l!=NULL && size==1)
    {
        if(flag==j)
        {
            p->etat=l;
            size=2;
        }
        j++;
        l=l->next;
    }
    printf("Veuillez tappez le nombre de personne avec qui ce patient a été en contact  : ");
    flag=sv_number(0,200);
    if(flag==0)
        p->prs=NULL;
    else
    {
        p->prs=malloc((flag+1)*sizeof(personne*));
        p->prs[flag]=NULL;
    }
    for(i=0; i<flag; i++)
    {
        *pr=ajouter_personne(*pr,lm);
        p->prs[i]=*pr;
    }
    p->next=lp;
    textcolor(CYAN+BLINK);
    cprintf("Modifications enregistrés \n");
    return p;
}
patient* chercher(patient*p,personne**pr,liste_maladies**l,etats*e)
{
    char n[30],*m;
    int i,flag,sexe;
    patient*tmp=p;
    if(p==NULL)
    {
        printf("Ops! Aucun patient enregistré ! \n");
        return p;
    }
    printf("Tappez le nombre correspondant au critere avec lequel vous voullez chercher :\n");
    printf("1-Le nom : \n");
    printf("2-Le prenom: \n");
    printf("3-L'age: \n");
    printf("4-Le sexe: \n");
    printf("5-Le CIN: \n");
    printf("6-Annuler: \n");
    i=sv_number(1,6);
    switch(i)
    {
    case 1 :
        fflush(stdin);
        printf("Veuillez saisir le nom du patient que vous cherchez : ");
        gets(n);
        n[19]='\0';
        flag=0;
        puts(tmp->nom);
        while(tmp!=NULL)
        {
            i=stricmp(tmp->nom,n);
            if(i==0)
            {
                afficher_patient(tmp,0);
                flag=1;
            }
            tmp=tmp->next;
        }
        if(flag==0)
        {
            printf("Aucun patient avec ce nom ! \n");
            return p;
        }
        break;
    case 2 :
        fflush(stdin);
        printf("Veuillez saisir le prenom du patient que vous cherchez : ");
        gets(n);
        n[19]='\0';
        flag=0;
        while(tmp!=NULL)
        {
            i=stricmp(tmp->prenom,n);
            if(i==0)
            {
                afficher_patient(tmp,0);
                flag=1;
            }
            tmp=tmp->next;
        }
        if(flag==0)
        {
            printf("Aucun patient avec ce prenom ! \n");
            return p;
        }
        break;
    case 3 :
        printf("Si c'est des femmes tappez 1 sinon 0 : ");
        sexe=sv_number(0,1);
        if(sexe==1)
            n[0]='F';
        else
            n[0]='H';
        flag=0;
        while(tmp!=NULL)
        {

            if(n[0]==tmp->sexe)
            {
                afficher_patient(tmp,0);
                flag=1;
            }
            tmp=tmp->next;
        }
        if(flag==0)
        {
            printf("Aucun patient avec ce prenom ! \n");
            return p;
        }
        break;
    case 4 :
        printf("Veuillez saisir l'age des patients que vous cherchez : ");
        i=sv_number(1,150);
        flag=0;
        while(tmp!=NULL)
        {
            if(tmp->age==i)
            {
                afficher_patient(tmp,0);
                flag=1;
            }
            tmp=tmp->next;
        }
        if(flag!=1)
        {
            printf("Aucun patient avec cette age ! \n");
            return p;
        }
        break;
    case 5 :
        m=sv_CIN();
        while(tmp!=NULL && i!=0)
        {
            i=stricmp(tmp->CIN,m);
            if(i==0)
            {
                printf("\n \n");
                afficher_patient(tmp,0);
            }
            tmp=tmp->next;
        }
        if(i!=0)
        {
            printf("Aucun patient avec ce CIN ! \n");
            free(m);
            return p;
        }
        break;
    case 6:
        return p;
    }
}
patient* affectation_pt_hopit(hopital*h,patient*pt)
{
    hopital*hp=h,*hp_proche;
    patient *tmp=pt;
    int i=1,code_proche,flag;
    char*m;
    fflush(stdin);
    if(hp==NULL)
    {
        printf("Affectation impossible ! Aucun hopital enregistré \n");
        return pt;
    }
    m=sv_CIN();
    while(tmp!=NULL && i!=0)
    {
        i=stricmp(tmp->CIN,m);
        if(i!=0)
        {
            tmp=tmp->next;
        }
    }
    if(i!=0)
    {
        printf("Ops! Aucun patient avec ce CIN ! \n");
        free(m);
        return pt;
    }
    else
    {
        if(pt->hopit!=NULL)
        {
            printf("Ce patient est deja affecté à un hopital \n");
            return pt;
        }
        //si on veut trvailler avec les codes postaux juste pour l egalité
        while(hp!=NULL)
        {
            if(hp->ad->code==tmp->ad->code && ((hp->lits_norm>0)||(hp->lits_rea>0)||(hp->salles_speci>0)))
            {
                tmp->hopit=hp;
                return pt;
            }
            hp=hp->next;
        }
        hp=h;
        hp_proche=hp;
        code_proche=hp->ad->code;
        flag=0; //si on veut travailler vc les villes quartiers et les rues
        while(hp!=NULL && flag!=1)
        {
            if((hp->lits_norm>0)||(hp->lits_rea>0)||(hp->salles_speci>0))
            {
                if(stricmp(hp->ad->ville,hp_proche->ad->ville)==0)
                {
                    if(strcmp(hp->ad->quartier,hp_proche->ad->quartier)==0)
                    {
                        if(strcmp(hp->ad->rue,hp_proche->ad->rue)==0)
                        {
                            code_proche=hp->ad->code;
                            hp_proche=hp;
                            flag=1;
                        }
                        if(flag!=1)
                            flag=2;
                    }
                    if(flag!=1 && flag!=2)
                        flag=3;
                }
            }
            hp=hp->next;
        }
        if(flag==1 || flag==2 || flag==3)
        {
            tmp->hopit=hp_proche;
            textcolor(CYAN+BLINK);
            cprintf("Modifications enregistrés \n");
        }
        else
            printf("Aucun hopital avec places disponiles !\n");
    }
    return pt;
}
personne* affectation_pr_hotel(hotel*h,personne*pr)
{
    hotel*ht=h,*ht_proche;
    personne *tmp=pr;
    int i=1,code_proche,flag;
    char*m;
    if(ht==NULL)
    {
        printf("Affectation impossible ! Aucun hotel enregistré \n");
        return pr;
    }
    if(pr==NULL)
    {
        printf("Affectation impossible ! Aucun patient enregistré \n");
        return pr;
    }
    fflush(stdin);
    m=sv_CIN();
    while(tmp!=NULL && i!=0)
    {
        i=stricmp(tmp->CIN,m);
        if(i!=0)
        {
            tmp=tmp->next;
        }
    }
    if(i!=0)
    {
        printf("Ops! Aucune personne enregistrée avec ce CIN ! \n");
        free(m);
        return pr;
    }
    else
    {
        if(tmp->hot->dispo!=-6)
        {
            printf("Cette personne est deja affectée à un hotel \n");
            return pr;
        }
        while(ht!=NULL)
        {
            if(ht->ad->code==tmp->hot->ad->code && ht->dispo>0)
            {
                printf("cc");
                free(tmp->hot->ad->ville);
                free(tmp->hot->ad->quartier);
                free(tmp->hot->ad->rue);
                free(tmp->hot->ad);
                free(tmp->hot);
                tmp->hot=ht;
                return pr;
            }
            ht=ht->next;
        }
        ht=h;
        ht_proche=ht;
        code_proche=ht->ad->code;
        flag=0;
        while(ht!=NULL && flag!=1)
        {
            if(ht->dispo>0)
            {
                if(stricmp(ht->ad->ville,ht_proche->ad->ville)==0)
                {
                    if(strcmp(ht->ad->quartier,ht_proche->ad->quartier)==0)
                    {
                        if(strcmp(ht->ad->rue,ht_proche->ad->rue)==0)
                        {
                            code_proche=ht->ad->code;
                            ht_proche=ht;
                            flag=1;
                        }
                        if(flag!=1)
                            flag=2;
                    }
                    if(flag!=1 && flag!=2)
                        flag=3;
                }
            }
            ht=ht->next;
        }
        if(flag==1 || flag==2 || flag==3)
        {
            tmp->hot=ht_proche;
            (tmp->hot->dispo)--;
            textcolor(CYAN+BLINK);
            cprintf("Modifications enregistrés \n");
        }
        else
            printf("Aucun hopital avec places disponiles !\n");
    }
    return pr;
}
patient* modifier_etat(patient*p,etats* e)
{
    int i=1,j=0,flag,size,help;
    patient*tmp=p,*previous=p;
    char*m;
    if(p==NULL)
    {
        printf("Affectation impossible ! Aucun patient enregistré \n");
        return p;
    }
    fflush(stdin);
    m=sv_CIN();
    while(tmp!=NULL && i!=0)
    {
        i=stricmp(tmp->CIN,m);
        if(i!=0)
        {
            previous=tmp;
            tmp=tmp->next;
        }
    }
    if(i!=0)
    {
        printf("Ops! Aucun patient enregistré avec ce CIN ! \n");
        free(m);
        return p;
    }
    else
    {
        afficher_liste_etats(e,1);
        printf("Veuillez tappez le nombre correspondant à l'etat du patient : ");
        flag=sv_number(0,5);
        i=0;
        while(e!=NULL)
        {
            if(i==flag)
            {
                previous->etat=e;
            }
            i++;
            e=e->next;
        }
        size=1;
        if(flag==4||flag==5)
        {
            printf("Puisque le patient est guéri voullez vous le supprimer ? si oui veuillez tapper 1 sinon 0 : ");
            help=sv_number(0,1);
            if(help==1)
            {
                if(p==previous)
                {
                    p=p->next;
                }
                else
                    previous->next=tmp->next;
                printf("1");
                free(tmp->ad->ville);
                free(tmp->ad->quartier);
                free(tmp->ad->rue);
                free(tmp->CIN);
                free(tmp->email);
                if(tmp->maladies!=NULL)
                    free(tmp->maladies);
                free(tmp->nom);
                free(tmp->prenom);
                if(tmp->prs!=NULL)
                    free(tmp->prs);
                free(tmp);
            }

        }
        return p;
    }
}
void menu(liste_maladies**lm,etats**le,personne**pr,patient**pt,hopital**hp,hotel**ht)
{
    int cpt=0,choix=0;
    char cc;
    printf("Menu : \n");
    printf("1-Ajouter un hopital\n");
    printf("2-Modifier un hopital \n");
    printf("3-Afficher la liste des hopitaux  \n");
    printf("4-Ajouter un hotel \n");
    printf("5-Modifier un hotel \n");
    printf("6-Afficher la liste des hotels \n");
    printf("7-Ajouter un patient \n");
    printf("8-Chercher un patient \n");
    printf("9-Affecter un patient à un hopital \n");
    printf("10-Modifier l'etat d'un patient \n");
    printf("11-Afficher la liste des patients \n");
    printf("12-Affecter un confiné à un hopital \n");
    printf("13-Afficher la liste des confinés \n");
    printf("14-Quitter  \n");
    printf("Veuillez choisir ");
    do
    {
        cc = getch();
        if (cpt==1 && cc >='0' && cc <= '4' && choix==1)
        {
            printf("%c", cc);
            choix=choix*10+(cc-'0');
            cpt++;
        }
        if(cpt==0 && cc >= '1' && cc <= '9')
        {
            printf("%c", cc);
            choix=cc-'0';
            cpt++;
        }
    }
    while(cc!=ENTRER || cpt==0);
    clrscr();
    switch(choix)
    {
    case 1 :
        *hp=ajouter_hopital(*hp);
        textcolor(CYAN+BLINK);
        cprintf("Modifications enregistrés \n");
        break;
    case 2 :
        *hp=modifier_hopital(*hp);
        break;
    case 3 :
        afficher_hopital(*hp,1);
        break;
    case 4 :
        *ht=ajouter_hotel(*ht,1);
        textcolor(CYAN+BLINK);
        cprintf("Modifications enregistrés \n");
        break;
    case 5 :
        *ht=modifier_hotel(*ht);
        break;
    case 6 :
        afficher_hotel(*ht,1);
        break;
    case 7 :
        *pt=ajouter_patient(*pt,pr,lm,*le);
        break;
    case 8 :
        chercher(*pt,pr,lm,*le);
        break;
    case 9 :
        affectation_pt_hopit(*hp,*pt);
        break;
    case 10 :
        *pt=modifier_etat(*pt,*le);
        break;
    case 11 :
        afficher_patient(*pt,1);
        break;
    case 12 :
        affectation_pr_hotel(*ht,*pr);
        break;
    case 13 :
        afficher_personne(*pr,1);
        break;
    case 14 :
        textcolor(CYAN+BLINK);
        cprintf("Merci ! Au revoir \n");
        exit(0);
        break;
    }
    getch();
    clrscr();
    menu(lm,le,pr,pt,hp,ht);
}
