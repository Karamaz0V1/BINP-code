
// Erosion et dilatation
int applique_masque_dilatation( imat im, imat masque, int i, int j );
imat dilatation( imat im, imat masque );
int applique_masque_erosion( imat im, imat masque, int i, int j );
imat erosion( imat im, imat masque );
imat dilatation_dual( imat im, imat masque );
imat erosion_dual( imat im, imat masque );

// Ouverture et fermeture
imat ouverture( imat im, imat masque );
imat fermeture( imat im, imat masque );
imat ouverture_dual( imat im, imat masque );
imat fermeture_dual( imat im, imat masque );

// Annexes
int pasDepassement(imat im, int i, int j);
