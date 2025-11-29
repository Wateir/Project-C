#ifndef __MACRO_H__
#define __MACRO_H__

#ifdef DEBUG
#define TEST_EXISTANCE(pointeur,NomFonction,MessageErreur,ValeurRetour) \
    if ((pointeur) == NULL) { \
        fprintf(stderr, "%s : %s\n", NomFonction, MessageErreur); \
        return ValeurRetour;\
    }
#else
#define TEST_EXISTANCE(pointeur,NomFonction,MessageErreur,ValeurRetour)\
    if ((pointeur) == NULL) { \
    return ValeurRetour;\
    }
#endif

/*
 TEST():
 Si le test retourne 1 affiche un message sur stderr si la macro DEBUG n'est pas presente
 Le programe retourne 1 passant au shell l'information d'une erreur
 */
#ifndef DEBUG
#define TEST(NomFonctionTest,ParametreFonction,TypeDebug) \
    if (NomFonctionTest(ParametreFonction)){ \
        fprintf(stderr, "%s à loupé, make %s à peut-être plus d'information\n",#NomFonctionTest,TypeDebug);\
        return 1;}
#else
#define TEST(NomFonctionTest,ParametreFonction,TypeDebug) if (NomFonctionTest(ParametreFonction))return 1;
#endif

#ifdef DEBUG
#define RETOURNE_ERREUR(NomFonction,ValeurRetour,MessageErreur,EtapeOptionnel){\
    fprintf(stderr, "%s : %s", #NomFonction, MessageErreur); \
    EtapeOptionnel \
    return ValeurRetour;\
    }
#else
#define RETOURNE_ERREUR(NomFonction,ValeurRetour,MessageErreur,EtapeOptionnel){\
    EtapeOptionnel \
    return ValeurRetour;\
    }
#endif

#endif
