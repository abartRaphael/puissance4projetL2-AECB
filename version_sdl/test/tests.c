/*
 *  Simple example of a CUnit unit test.
 *
 *  This program (crudely) demonstrates a very simple "black box"
 *  test of the standard library functions fprintf() and fread().
 *  It uses suite initialization and cleanup functions to open
 *  and close a common temporary file used by the test functions.
 *  The test functions then write to and read from the temporary
 *  file in the course of testing the library functions.
 *
 *  The 2 test functions are added to a single CUnit suite, and
 *  then run using the CUnit Basic interface.  The output of the
 *  program (on CUnit version 2.0-2) is:
 *
 *           CUnit : A Unit testing framework for C.
 *           http://cunit.sourceforge.net/
 *
 *       Suite: Suite_1
 *         Test: test of fprintf() ... passed
 *         Test: test of fread() ... passed
 *
 *       --Run Summary: Type      Total     Ran  Passed  Failed
 *                      suites        1       1     n/a       0
 *                      tests         2       2       2       0
 *                      asserts       5       5       5       0
 */

#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>



#include "../lib/fonc2.h"
#include "../lib/foncSdl.h"

// Pointer to the file used by the tests. 
static FILE* temp_file = NULL;

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void)
{
	if (NULL == (temp_file = fopen("temp.txt", "w+"))) {
	  return -1;
	}
	else {
	  return 0;
	}
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void)
{
	if (0 != fclose(temp_file)) {
	  return -1;
	}
	else {
	  temp_file = NULL;
	  return 0;
	}
}



// tests of functions

void test_initGrille(void)
{
	t_pion grille[LIGNES][COLONNES];

	if (NULL != temp_file) {
		initGrille(grille);
		CU_ASSERT_EQUAL(grille[0][0].couleur, vide);
		CU_ASSERT_EQUAL(grille[0][0].type, no_type);
		CU_ASSERT_EQUAL(grille[LIGNES-1][COLONNES-1].couleur, vide);
		CU_ASSERT_EQUAL(grille[LIGNES-1][COLONNES-1].type, no_type);
	}	
}


void test_estPleine(void) 
{
	t_pion grille[LIGNES][COLONNES];

	initGrille(grille);

	//cas avec une colonne vide
	grille[LIGNES-1][0].couleur = vide;
	//cas avec une pièce
	grille[LIGNES-1][1].couleur = rouge;
	//cas avec deux pièces
	grille[LIGNES-1][2].couleur = jaune;
	grille[LIGNES-2][2].couleur = rouge;
	//cas avec une colonne pleine
	grille[LIGNES-1][3].couleur = rouge;
	grille[LIGNES-2][3].couleur = rouge;
	grille[LIGNES-3][3].couleur = rouge;
	grille[LIGNES-4][3].couleur = jaune;
	grille[LIGNES-5][3].couleur = rouge;
	grille[LIGNES-6][3].couleur = rouge;

	if (NULL != temp_file) {
		CU_ASSERT_FALSE(estPleine(grille, 0));
		CU_ASSERT_FALSE(estPleine(grille, 1));
		CU_ASSERT_FALSE(estPleine(grille, 2));
		CU_ASSERT_TRUE(estPleine(grille, 3));
	}	
}


void test_caseLibre(void) 
{
	t_pion grille[LIGNES][COLONNES];

	initGrille(grille);

	//cas avec une colonne vide
	grille[LIGNES-1][0].couleur = vide;
	//cas avec une pièce
	grille[LIGNES-1][1].couleur = rouge;
	//cas avec deux pièces
	grille[LIGNES-1][2].couleur = jaune;
	grille[LIGNES-2][2].couleur = rouge;
	//cas avec une colonne pleine
	grille[LIGNES-1][3].couleur = rouge;
	grille[LIGNES-2][3].couleur = rouge;
	grille[LIGNES-3][3].couleur = rouge;
	grille[LIGNES-4][3].couleur = jaune;
	grille[LIGNES-5][3].couleur = rouge;
	grille[LIGNES-6][3].couleur = rouge;

	if (NULL != temp_file) {
		CU_ASSERT_EQUAL(caseLibre(grille, 0),5);
		CU_ASSERT_EQUAL(caseLibre(grille, 1),4);
		CU_ASSERT_EQUAL(caseLibre(grille, 2),3);
		CU_ASSERT_EQUAL(caseLibre(grille, 3),-1);
	}	
}


void test_ajoutPion(void) 
{
	t_pion grille[LIGNES][COLONNES], 
		piece;

	initGrille(grille);

	if (NULL != temp_file) {

		//cas avec le type t_type no_type pour la pièce à ajouter
		grille[LIGNES-1][0].couleur = rouge;
		grille[LIGNES-1][0].type = pleine;
		piece.couleur = vide;
		piece.type = no_type;
		CU_ASSERT_TRUE(ajoutPion(grille, 0, piece));
			//vérifier que la pièce n'a pas été ajoutée
		CU_ASSERT_EQUAL(grille[LIGNES-2][0].couleur, vide);
		CU_ASSERT_EQUAL(grille[LIGNES-2][0].type, no_type);

		//cas avec une colonne vide
		grille[LIGNES-1][0].couleur = vide;
		grille[LIGNES-1][0].type = no_type;
		piece.couleur = rouge;
		piece.type = pleine;
		CU_ASSERT_FALSE(ajoutPion(grille, 0, piece));
			//vérifier que la pièce a bien été ajoutée au bon endroit
		CU_ASSERT_EQUAL(grille[LIGNES-1][0].couleur, piece.couleur);
		CU_ASSERT_EQUAL(grille[LIGNES-1][0].type, piece.type);


		//cas (plusieurs) où on joue une pièce CREUSE,
		piece.type = creuse;
		//... sur une pièce creuse,
		//...... de couleur différente
		piece.couleur = rouge;
		grille[LIGNES-1][1].couleur = jaune;
		grille[LIGNES-1][1].type = creuse;
		CU_ASSERT_FALSE(ajoutPion(grille, 1, piece));
		CU_ASSERT_EQUAL(grille[LIGNES-1][1].couleur, jauneRouge);
		CU_ASSERT_EQUAL(grille[LIGNES-1][1].type, bloquante);
		//...... de couleur différente (inverse)
		piece.couleur = jaune;
		grille[LIGNES-1][1].couleur = rouge;
		grille[LIGNES-1][1].type = creuse;
		CU_ASSERT_FALSE(ajoutPion(grille, 1, piece));
		CU_ASSERT_EQUAL(grille[LIGNES-1][1].couleur, rougeJaune);
		CU_ASSERT_EQUAL(grille[LIGNES-1][1].type, bloquante);
		//...... de même couleur
		piece.couleur = rouge;
		grille[LIGNES-1][1].couleur = rouge;
		grille[LIGNES-1][1].type = creuse;
		CU_ASSERT_FALSE(ajoutPion(grille, 1, piece));
		CU_ASSERT_EQUAL(grille[LIGNES-1][1].couleur, piece.couleur);
		CU_ASSERT_EQUAL(grille[LIGNES-1][1].type, bloquante);

		//... sur une pièce pleine,
		//...... de couleur différente
		piece.couleur = rouge;
		grille[LIGNES-1][1].couleur = jaune;
		grille[LIGNES-1][1].type = pleine;
		CU_ASSERT_FALSE(ajoutPion(grille, 1, piece));
		CU_ASSERT_EQUAL(grille[LIGNES-1][1].couleur, rougeJaune);
		CU_ASSERT_EQUAL(grille[LIGNES-1][1].type, bloquante);
		//...... de couleur différente (inverse)
		piece.couleur = jaune;
		grille[LIGNES-1][1].couleur = rouge;
		grille[LIGNES-1][1].type = pleine;
		CU_ASSERT_FALSE(ajoutPion(grille, 1, piece));
		CU_ASSERT_EQUAL(grille[LIGNES-1][1].couleur, jauneRouge);
		CU_ASSERT_EQUAL(grille[LIGNES-1][1].type, bloquante);
		//...... de même couleur
		piece.couleur = rouge;
		grille[LIGNES-1][1].couleur = rouge;
		grille[LIGNES-1][1].type = pleine;
		CU_ASSERT_FALSE(ajoutPion(grille, 1, piece));
		CU_ASSERT_EQUAL(grille[LIGNES-1][1].couleur, piece.couleur);
		CU_ASSERT_EQUAL(grille[LIGNES-1][1].type, bloquante);

		//... sur une pièce bloquante,
		piece.couleur = rouge;
		grille[LIGNES-1][1].type = bloquante;
		CU_ASSERT_FALSE(ajoutPion(grille, 1, piece));
		CU_ASSERT_EQUAL(grille[LIGNES-2][1].couleur, piece.couleur);
		CU_ASSERT_EQUAL(grille[LIGNES-2][1].type, piece.type);
			grille[LIGNES-2][1].couleur = vide;
			grille[LIGNES-2][1].type = no_type;

		//====

		//cas (plusieurs) où on joue une pièce PLEINE,
		piece.type = pleine;
		//... sur une pièce creuse,
		//...... de couleur différente
		piece.couleur = rouge;
		grille[LIGNES-1][1].couleur = jaune;
		grille[LIGNES-1][1].type = creuse;
		CU_ASSERT_FALSE(ajoutPion(grille, 1, piece));
		CU_ASSERT_EQUAL(grille[LIGNES-1][1].couleur, jauneRouge);
		CU_ASSERT_EQUAL(grille[LIGNES-1][1].type, bloquante);
		//...... de couleur différente (inverse)
		piece.couleur = jaune;
		grille[LIGNES-1][1].couleur = rouge;
		grille[LIGNES-1][1].type = creuse;
		CU_ASSERT_FALSE(ajoutPion(grille, 1, piece));
		CU_ASSERT_EQUAL(grille[LIGNES-1][1].couleur, rougeJaune);
		CU_ASSERT_EQUAL(grille[LIGNES-1][1].type, bloquante);
		//...... de même couleur
		piece.couleur = rouge;
		grille[LIGNES-1][1].couleur = rouge;
		grille[LIGNES-1][1].type = creuse;
		CU_ASSERT_FALSE(ajoutPion(grille, 1, piece));
		CU_ASSERT_EQUAL(grille[LIGNES-1][1].couleur, piece.couleur);
		CU_ASSERT_EQUAL(grille[LIGNES-1][1].type, bloquante);

		//... sur une pièce pleine,
		piece.couleur = rouge;
		grille[LIGNES-1][1].type = pleine;
		CU_ASSERT_FALSE(ajoutPion(grille, 1, piece));
		CU_ASSERT_EQUAL(grille[LIGNES-2][1].couleur, piece.couleur);
		CU_ASSERT_EQUAL(grille[LIGNES-2][1].type, piece.type);
			grille[LIGNES-2][1].couleur = vide;
			grille[LIGNES-2][1].type = no_type;

		//... sur une pièce bloquante,
		grille[LIGNES-1][1].type = bloquante;
		CU_ASSERT_FALSE(ajoutPion(grille, 1, piece));
		CU_ASSERT_EQUAL(grille[LIGNES-2][1].couleur, piece.couleur);
		CU_ASSERT_EQUAL(grille[LIGNES-2][1].type, piece.type);
			grille[LIGNES-2][1].couleur = vide;
			grille[LIGNES-2][1].type = no_type;

		//====

		//cas (plusieurs) où on joue une pièce BLOQUANTE,
		piece.type = bloquante;
		piece.couleur = jaune;
		//... sur une pièce creuse,
		grille[LIGNES-1][1].couleur = rouge;
		grille[LIGNES-1][1].type = creuse;
		CU_ASSERT_FALSE(ajoutPion(grille, 1, piece));
		CU_ASSERT_EQUAL(grille[LIGNES-2][1].couleur, piece.couleur);
		CU_ASSERT_EQUAL(grille[LIGNES-2][1].type, piece.type);
			grille[LIGNES-2][1].couleur = vide;
			grille[LIGNES-2][1].type = no_type;

		//... sur une pièce pleine,
		grille[LIGNES-1][1].type = pleine;
		CU_ASSERT_FALSE(ajoutPion(grille, 1, piece));
		CU_ASSERT_EQUAL(grille[LIGNES-2][1].couleur, piece.couleur);
		CU_ASSERT_EQUAL(grille[LIGNES-2][1].type, piece.type);
			grille[LIGNES-2][1].couleur = vide;
			grille[LIGNES-2][1].type = no_type;

		//... sur une pièce bloquante,
		grille[LIGNES-1][1].type = bloquante;
		CU_ASSERT_FALSE(ajoutPion(grille, 1, piece));
		CU_ASSERT_EQUAL(grille[LIGNES-2][1].couleur, piece.couleur);
		CU_ASSERT_EQUAL(grille[LIGNES-2][1].type, piece.type);
			grille[LIGNES-2][1].couleur = vide;
			grille[LIGNES-2][1].type = no_type;
			


		//cas avec une colonne pleine
		grille[LIGNES-1][3].couleur = rouge;
		grille[LIGNES-2][3].couleur = rouge;
		grille[LIGNES-3][3].couleur = rouge;
		grille[LIGNES-4][3].couleur = jaune;
		grille[LIGNES-5][3].couleur = rouge;
		grille[LIGNES-6][3].couleur = rouge;
		CU_ASSERT_TRUE(ajoutPion(grille, 3, piece));
	}	
}


void test_quatreALaSuiteHorizontal(void) 
{
	t_pion grille[LIGNES][COLONNES], 
		piece;

	initGrille(grille);

	grille[LIGNES-1][0].couleur = rouge;
	grille[LIGNES-1][1].couleur = rouge;
	grille[LIGNES-1][2].couleur = rouge;
	grille[LIGNES-1][3].couleur = rouge;

	piece.couleur = rouge;

	if (NULL != temp_file) {
		CU_ASSERT_TRUE(quatreALaSuiteHorizontal(grille, LIGNES-1, 0, piece));
		CU_ASSERT_TRUE(quatreALaSuiteHorizontal(grille, LIGNES-1, 3, piece));
	}	
}


void test_quatreALaSuiteDiagonale1(void) 
{
	t_pion grille[LIGNES][COLONNES], 
		piece;

	initGrille(grille);

	piece.couleur = rouge;

	if (NULL != temp_file) {

		/*	X - - - - - -
		 * 	- X - - - - -
		 * 	- - X - - - -
		 * 	- - - X - - -
		 * 	- - - - - - -
		 * 	- - - - - - -
		 */
		grille[LIGNES-6][0].couleur = rouge;
		grille[LIGNES-5][1].couleur = rouge;
		grille[LIGNES-4][2].couleur = rouge;
		grille[LIGNES-3][3].couleur = rouge;
		CU_ASSERT_TRUE(quatreALaSuiteDiagonale1(grille, LIGNES-6, 0, piece));
		CU_ASSERT_TRUE(quatreALaSuiteDiagonale1(grille, LIGNES-5, 1, piece));
		CU_ASSERT_TRUE(quatreALaSuiteDiagonale1(grille, LIGNES-4, 2, piece));
		CU_ASSERT_TRUE(quatreALaSuiteDiagonale1(grille, LIGNES-3, 3, piece));

		initGrille(grille);

		/*	- - - - - - -
		 * 	- - - - - - -
		 * 	X - - - - - -
		 * 	- X - - - - -
		 * 	- - X - - - -
		 * 	- - - X - - -
		 */
		grille[LIGNES-4][0].couleur = rouge;
		grille[LIGNES-3][1].couleur = rouge;
		grille[LIGNES-2][2].couleur = rouge;
		grille[LIGNES-1][3].couleur = rouge;
		CU_ASSERT_TRUE(quatreALaSuiteDiagonale1(grille, LIGNES-4, 0, piece));
		CU_ASSERT_TRUE(quatreALaSuiteDiagonale1(grille, LIGNES-3, 1, piece));
		CU_ASSERT_TRUE(quatreALaSuiteDiagonale1(grille, LIGNES-2, 2, piece));
		CU_ASSERT_TRUE(quatreALaSuiteDiagonale1(grille, LIGNES-1, 3, piece));

		initGrille(grille);

		/*	- - - X - - -
		 * 	- - - - X - -
		 * 	- - - - - X -
		 * 	- - - - - - X
		 * 	- - - - - - -
		 * 	- - - - - - -
		 */
		grille[LIGNES-6][3].couleur = rouge;
		grille[LIGNES-5][4].couleur = rouge;
		grille[LIGNES-4][5].couleur = rouge;
		grille[LIGNES-3][6].couleur = rouge;
		CU_ASSERT_TRUE(quatreALaSuiteDiagonale1(grille, LIGNES-6, 3, piece));
		CU_ASSERT_TRUE(quatreALaSuiteDiagonale1(grille, LIGNES-5, 4, piece));
		CU_ASSERT_TRUE(quatreALaSuiteDiagonale1(grille, LIGNES-4, 5, piece));
		CU_ASSERT_TRUE(quatreALaSuiteDiagonale1(grille, LIGNES-3, 6, piece));

		initGrille(grille);

		/*	- - - - - - -
		 * 	- - X - - - -
		 * 	- - - X - - -
		 * 	- - - - X - -
		 * 	- - - - - X -
		 * 	- - - - - - -
		 */
		grille[LIGNES-5][2].couleur = rouge;
		grille[LIGNES-4][3].couleur = rouge;
		grille[LIGNES-3][4].couleur = rouge;
		grille[LIGNES-2][5].couleur = rouge;
		CU_ASSERT_TRUE(quatreALaSuiteDiagonale1(grille, LIGNES-5, 2, piece));
		CU_ASSERT_TRUE(quatreALaSuiteDiagonale1(grille, LIGNES-4, 3, piece));
		CU_ASSERT_TRUE(quatreALaSuiteDiagonale1(grille, LIGNES-3, 4, piece));
		CU_ASSERT_TRUE(quatreALaSuiteDiagonale1(grille, LIGNES-2, 5, piece));

		initGrille(grille);

		/*	- - - - - - -
		 * 	- - X - - - -
		 * 	- - - X - - -
		 * 	- - - - - - -
		 * 	- - - - - X -
		 * 	- - - - - - X
		 */
		grille[LIGNES-5][2].couleur = rouge;
		grille[LIGNES-4][3].couleur = rouge;
		grille[LIGNES-2][5].couleur = rouge;
		grille[LIGNES-1][6].couleur = rouge;
		CU_ASSERT_FALSE(quatreALaSuiteDiagonale1(grille, LIGNES-5, 2, piece));
		CU_ASSERT_FALSE(quatreALaSuiteDiagonale1(grille, LIGNES-4, 3, piece));
		CU_ASSERT_FALSE(quatreALaSuiteDiagonale1(grille, LIGNES-2, 5, piece));
		CU_ASSERT_FALSE(quatreALaSuiteDiagonale1(grille, LIGNES-1, 6, piece));

		initGrille(grille);

		/*	- - - - - - -
		 * 	- - @ - - - -
		 * 	- - - X - - -
		 * 	- - - - @ - -
		 * 	- - - - - X -
		 * 	- - - - - - -
		 */
		grille[LIGNES-5][2].couleur = rougeJaune;
		grille[LIGNES-4][3].couleur = rouge;
		grille[LIGNES-3][4].couleur = jauneRouge;
		grille[LIGNES-2][5].couleur = rouge;
		CU_ASSERT_TRUE(quatreALaSuiteDiagonale1(grille, LIGNES-5, 2, piece));
		CU_ASSERT_TRUE(quatreALaSuiteDiagonale1(grille, LIGNES-4, 3, piece));
		CU_ASSERT_TRUE(quatreALaSuiteDiagonale1(grille, LIGNES-3, 4, piece));
		CU_ASSERT_TRUE(quatreALaSuiteDiagonale1(grille, LIGNES-2, 5, piece));
	}	
}


/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
	CU_pSuite pSuite = NULL;

	// initialize the CUnit test registry 
	if (CUE_SUCCESS != CU_initialize_registry())
	  return CU_get_error();

	// add a suite to the registry 
	pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
	if (NULL == pSuite) {
	  CU_cleanup_registry();
	  return CU_get_error();
	}

	// add the tests to the suite
	// NOTE - ORDER IS IMPORTANT(?)
	if ((NULL == CU_add_test(pSuite, "test of initGrille()", test_initGrille))
	|| (NULL == CU_add_test(pSuite, "test of estPleine()", test_estPleine))
	|| (NULL == CU_add_test(pSuite, "test of caseLibre()", test_caseLibre))
	|| (NULL == CU_add_test(pSuite, "test of ajoutPion()", test_ajoutPion))
	|| (NULL == CU_add_test(pSuite, "test of quatreALaSuiteHorizontal()", test_quatreALaSuiteHorizontal))
	|| (NULL == CU_add_test(pSuite, "test of quatreALaSuiteDiagonale1()", test_quatreALaSuiteDiagonale1)))
	{
	  CU_cleanup_registry();
	  return CU_get_error();
	}

	// Run all tests using the CUnit Basic interface 
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}

