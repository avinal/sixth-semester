input_image = imread('download.jfif'); 
 image = rgb2gray(input_image);
[M, N] = size(image); 
 
FT_img = fft2(double(image)); 

D0 = 30;  

u = 0:(M-1); 
idx = find(u>M/2); 
u(idx) = u(idx)-M; 
v = 0:(N-1); 
idy = find(v>N/2); 
v(idy) = v(idy)-N; 
 
[V, U] = meshgrid(v, u); 

D = sqrt(U.^2+V.^2); 


H = double(D <= D0); 

G = H.*FT_img; 


output_image = real(ifft2(double(G))); 

subplot(2, 1, 1), imshow(input_image), 
subplot(2, 1, 2), imshow(output_image, [ ]); 
