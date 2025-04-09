import numpy as np
import cv2
from matplotlib import pyplot as plt

def lowpassFilter(matrix):
  filtered_matrix = cv2.blur(matrix, ksize=(3,3))
  print("\nFiltered (Lowpass - blur 3x3) Matrix:")
  print(filtered_matrix)
  return filtered_matrix

def visualization(matrix, filtered_matrix):
  plt.figure(figsize=(10, 4))

  plt.subplot(1, 2, 1)
  plt.title('Original Image')
  plt.imshow(matrix, cmap='gray', vmin=0, vmax=255)
  plt.colorbar()
  
  plt.subplot(1, 2, 2)
  plt.title('Filtered Image (3x3)')
  plt.imshow(filtered_matrix, cmap='gray', vmin=0, vmax=255)
  plt.colorbar()

  plt.tight_layout()
  plt.show()

matrix = np.array([
  [29, 10, 12, 13],
  [34, 12, 13, 13],
  [31, 10, 11, 12],
  [30, 11, 14, 14],
  [31, 12, 12, 11]
], dtype=np.uint8)

print("Input Matrix:")
print(matrix)

lowpassFilter(matrix)
visualization(matrix, lowpassFilter(matrix))