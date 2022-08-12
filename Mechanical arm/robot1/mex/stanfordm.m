L{1}=link([    0 0 0 0 0 1 0  0 -1 1 1 1 0 0 0 291e-6  -62.6111], 'modified');
L{2}=link([-pi/2 0 0 1 0 1 0  0 -1 1 1 1 0 0 0 409e-6  107.815], 'modified');
L{3}=link([ pi/2 0 0 0 1 1 0  0 -1 1 1 1 0 0 0 299e-6  -53.7063], 'modified');
L{4}=link([    0 0 0 0 0 1 0  0 -1 7 11 0.5 2 -3 -9 291e-6     -62.6111], 'modified');
L{5}=link([-pi/2 0 0 0 0 1 0  0  1 3 4 2 6 3 5 409e-6  107.815], 'modified');
L{6}=link([ pi/2 0 0 1 0 1 0  0 -1 1 1 1 0 0 0 299e-6  -53.7063], 'modified');
stanm=robot(L, 'stanford');
clear L
