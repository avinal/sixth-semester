image = imread("basic.png");
imshow(image)
imwrite(image, "copy.jpeg")

img2 = imread("copy.jpeg");
imshow(img2)