%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% TP TSI : Morphologie mathematique
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear all;
close all;

% Images 'binaires' PGM : forme=255; fond=0;
Ibin= imread('./images/test_operateur_bin.pgm');
figure(1);
imshow(Ibin), title('image originale');


es=strel('square',3);
esbis = ones(3);

Ibin_dilat=imdilate(Ibin,es,'same');
 
Ibin_erod=imerode(Ibin,es,'same');
 
Ibin_open=imopen(Ibin,es);

Ibin_close=imclose(Ibin,es);

figure(2);
imshow(Ibin_dilat), title('Image obtenue apres dilatation Matlab');

figure(3);
imshow(Ibin_erod), title('Image obtenue apres erosion Matlab');

figure(4);
imshow(Ibin_close), title('Image obtenue apres fermeture Matlab'); 

figure(5);
imshow(Ibin_open), title('Image obtenue apres ouverture Matlab');

skel=bwmorph(Ibin,'skel',Inf);
figure(6);
imshow(skel), title('squelette');
