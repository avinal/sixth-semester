**********************************
Digital Image Processing Practices
**********************************

1. Simple image read and write operations

.. code-block:: python

    image = imread("basic.png");
    imshow(image)
    imwrite(image, "copy.jpeg")

    img2 = imread("copy.jpeg");
    imshow(img2)

Output
------

.. figure:: basic.png
    :alt: A planet with twilight rings
    :align: center
