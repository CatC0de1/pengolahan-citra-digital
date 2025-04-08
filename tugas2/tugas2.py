import cv2
import numpy as np
import matplotlib.pyplot as plt
import os

def image_to_matrix(image_path, crop_box):
    # Membaca file gambar\

    # jika mengguananakan relative path ('../images/kucing.png')
    # current_dir = os.path.dirname(__file__)
    # image_path = os.path.join(current_dir, image_path)
    
    img = cv2.imread(image_path)
    img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    
    plt.figure(figsize=(10, 5))
    plt.subplot(1, 4, 1)
    plt.imshow(img_rgb)
    plt.title("Original Image")
    plt.axis("off")
    
    # Memotong gambar sesuai dengan koordinat yang diberikan
    x1, y1, x2, y2 = crop_box
    cropped_img = img_gray[y1:y2, x1:x2]
    
    # Menambahkan kotak merah pada posisi crop
    img_with_box = cv2.cvtColor(img_gray, cv2.COLOR_GRAY2RGB)
    cv2.rectangle(img_with_box, (x1, y1), (x2, y2), (255, 0, 0), 2)
    
    plt.subplot(1, 4, 2)
    plt.imshow(img_gray, cmap='gray')
    plt.title("Grayscale Image")
    plt.axis("off")
    
    plt.subplot(1, 4, 3)
    plt.imshow(img_with_box)
    plt.title("Crop Position")
    plt.axis("off")
    
    plt.subplot(1, 4, 4)
    plt.imshow(cropped_img, cmap='gray')
    plt.title("Cropped Image")
    plt.axis("off")
    
    plt.show()
    
    # Mengonversi hasil ke dalam bentuk matriks
    img_matrix = np.array(cropped_img)
    
    return img_matrix


image_path = './images/kucing.png'  # image
crop_box = (70, 50, 90, 70)  # (left, upper, right, lower) dalam satuan pixel

matrix = image_to_matrix(image_path, crop_box)
print(matrix)
