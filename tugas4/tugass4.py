import cv2

img = cv2.imread('./kucing.png')

# alpha = kontras, beta = kecerahan
bright_img = cv2.convertScaleAbs(img, alpha=1.2, beta=50)

cv2.imshow('Original', img)
cv2.imshow('Brightened Image', bright_img)
cv2.waitKey(0)
cv2.destroyAllWindows()