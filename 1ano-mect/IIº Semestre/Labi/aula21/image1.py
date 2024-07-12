__author__ = 'labi'

from PIL import Image
from PIL import ExifTags
from PIL import ImageDraw
from PIL import ImageFont
import sys
import math

def imcar(fname):
    im = Image.open(fname)

    width, height = im.size

    print "Largura: %dpx" % width
    print "Altura: %dpx" % height
    print "Formato: %s" % im.format

    tags = im._getexif()

    for k,v in tags.items():
        print str(ExifTags.TAGS[k])+" : "+str(v)

def changedim(fname):
    im = Image.open(fname)
    width, height = im.size

    for s in [0.2, 8, 2]:
        dimension = (int(width*s), int(height*s))
        new_im = im.resize(dimension, Image.BILINEAR)
        new_im.save(fname+'-%.2f-bilinear.jpg'%s)

def compression(fname):
    im = Image.open(fname)

    for i in [1, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100]:
        im.save(fname+"-test-%i.jpg"%i, quality=i)

def changeformat(fname):
    im = Image.open(fname)

    for i in [20, 40, 60]:
        im.save(fname+"-test-%i.png"%i, quality=i)
        im.save(fname+"-test-%i.tiff"%i, quality=i)
        im.save(fname+"-test-%i.bmp"%i, quality=i)

def delete4bits(fname):
    im = Image.open(fname)

    width, height = im.size

    for x in xrange(width):
        for y in xrange(height):
            p = im.getpixel( (x,y) )

            r = p[0] & 0b11110000
            g = p[1] & 0b11110000
            b = p[2] & 0b11110000

            im.putpixel( (x,y), (r,g,b) )

    im.save(fname+'-4bits.jpg')

def changecolor(fname):
    im = Image.open(fname)

    width, height = im.size

    new_im = Image.new(im.mode, im.size)

    for x in range(width):
        for y in range(height):
            p = im.getpixel( (x,y) )
            r = p[1]
            g = p[0]
            b = p[2]
            new_im.putpixel((x,y), (r, g, b) )

    new_im.save(fname+'-4bits.jpg')

def negcolor(fname):
    im = Image.open(fname)

    width, height = im.size

    new_im = Image.new(im.mode, im.size)

    for x in range(width):
        for y in range(height):
            p = im.getpixel( (x,y) )
            r = 255-p[0]
            g = 255-p[1]
            b = 255-p[2]
            new_im.putpixel((x,y), (r, g, b) )

    new_im.save(fname+'-neg.jpg')

def cinza(fname):
    im = Image.open(fname)

    new_im = im.convert('L')

    new_im.save(fname+'-L.jpg')

def gray(fname):
    im = Image.open(fname)

    width, height = im.size
    new_im = Image.new('L', im.size)

    for x in xrange(width):
        for y in xrange(height):
            p = im.getpixel( (x,y) )
            l = int(p[0] * 0.299 + p[1]*0.587 + p[2]*0.144)
            new_im.putpixel( (x,y), (l) )

    new_im.save(fname+'-L.jpg')

def effect_intensity(im, f):
    img = Image.open(im)

    new_img = img.convert("YCbCr")
    width, height = img.size

    for x in xrange(width):
        for y in xrange(height):
            pixel = new_img.getpixel( (x,y) )
            py = min(255, int(pixel[0] * f))

            new_img.putpixel( (x,y), (py, pixel[1], pixel[2]))

    new_img.save(im+'-Intensity.jpg')

def gama(im, g):
    img = Image.open(im)

    new_img = img.convert("YCbCr")
    width, height = img.size

    f = 255/(math.pow(255, g))

    for x in xrange(width):
        for y in xrange(height):
            pixel = new_img.getpixel( (x,y) )
            py = int(math.pow(pixel[0], g)*f)
            new_img.putpixel( (x,y), (py, pixel[1], pixel[2]))

    new_img.save(im+'-gamac.jpg')

def satur(im, f):

    img = Image.open(im)

    new_img = img.convert("YCbCr")
    width, height = img.size

    for x in xrange(width):
        for y in xrange(height):
            pixel = new_img.getpixel( (x,y) )
            py = pixel[0]
            pb = min(255,int((pixel[1] - 128) * f) + 128)
            pr = min(255,int((pixel[2] - 128) * f) + 128)
            new_img.putpixel( (x,y), (py, pb, pr))

    new_img.save(im+'-satur.jpg')

def sepia(im):
    img = Image.open(im)

    width, height = img.size

    for x in xrange(width):
        for y in xrange(height):
            p = img.getpixel( (x,y) )

            r = p[0] *0.189 + p[1]*0.769 + p[2]*0.393
            g = p[0] *0.169 + p[1]*0.686 + p[2]*0.349
            b = p[0] *0.131 + p[1]*0.534 + p[2]*0.272

            img.putpixel( (x,y), (int(r),int(g),int(b)) )

    img.save(im+'-sepia.jpg')

def edgedetector(im):
    img = Image.open(im)
    width, height = img.size

    for x in xrange(width):
        for y in xrange(height):
            p = img.getpixel( (x,y) )
            p = is_edge(img, x, y, 50, True)

            img.putpixel( (x,y), (p[0],p[1],p[2]) )

    img.save(im+'-borders.jpg')



def is_edge(im, x, y, diff, bw):
    # Obter o pixel
    p = im.getpixel( (x , y) )
    width, height = im.size

    if x < width-1 and y < height-1 and x > 0 and y > 0:


        #Vizinhos superiores e inferiores
        for vx in xrange(-1,1):
            for vy in [-1, 1]:
                px = im.getpixel( (x + vx, y + vy) )

            if abs(p[0]- px[0]) > diff:
                return (0,128,128)

        #Vizinhos da esquerda e direita
        for vx in [-1, 1]:
            px = im.getpixel( (x + vx, y) )

            if abs(p[0]- px[0]) > diff:
                return (0,128,128)


    if bw :
        return (255,128,128)
    else:
        return p


def vignette(im):
    img = Image.open(im)
    width, height = img.size

    for x in xrange(width):
        for y in xrange(height):
            p = img.getpixel( (x,y) )
            p0 = int(p[0]*get_factor(x,y,width/2, height/2))
            p1 = int(p[1]*get_factor(x,y,width/2, height/2))
            p2 = int(p[2]*get_factor(x,y,width/2, height/2))


            img.putpixel( (x,y), (p0,p1,p2) )

    img.save(im+'-vignette.jpg')

def get_factor(x, y, xref, yref):
    distance = math.sqrt( pow(x-xref,2) + pow(y-yref,2))
    distance_to_edge = math.sqrt( pow(xref,2) + pow(yref,2))
    return 1-(distance/distance_to_edge) #Percentagem


def marcaagua(im1, im2, f):
    img1 = Image.open(im1)
    width, height = img1.size

    img2 = Image.open(im2)
    width2, height2 = img2.size
    start_x = 0
    start_y = 0

    for x in xrange(width2):
        for y in xrange(height2):
            p1 = img1.getpixel( (x+start_x, y+start_y) )
            p2 = img2.getpixel( (x,y) )


            r = int(p1[0]*(1-f)+p2[0]*f)
            g = int(p1[1]*(1-f)+p2[1]*f)
            b = int(p1[2]*(1-f)+p2[2]*f)

            img1.putpixel( (x,y), (r,g,b) )

    img1.save(im1+'-'+im2+'.jpg')

def marcaaguainvisivel(im1, im2):
    f = 0.8
    img1 = Image.open(im1)
    width, height = img1.size

    img2 = Image.open(im2)
    width2, height2 = img2.size
    start_x = 0
    start_y = 0

    for x in xrange(width2):
        for y in xrange(height2):
            p1 = img1.getpixel( (x+start_x, y+start_y) )
            p2 = img2.getpixel( (x,y) )


            r = p1[0] | (p2[0]>>7)
            g = p1[1] | (p2[1]>>7)
            b = p1[2] | (p2[2]>>7)

            img1.putpixel( (x,y), (r,g,b) )

    img1.save(im1+'-'+im2+'-inv.jpg')

def revelarmarcainvisivel(im1):
    f = 0.8
    img1 = Image.open(im1)
    width, height = img1.size

    start_x = 0
    start_y = 0

    for x in xrange(width):
        for y in xrange(height):
            p1 = img1.getpixel( (x, y) )


            r = (p1[0] << 7) & 255
            g = (p1[1] << 7) & 255
            b = (p1[2] << 7) & 255

            img1.putpixel( (x,y), (r,g,b) )

    img1.save(im1+'-invrev.jpg')

def text(img, text):
    im = Image.open(img)
    width, height = im.size

    draw = ImageDraw.Draw(im)
    font = ImageFont.truetype('/usr/share/fonts/truetype/freefont/FreeMono.ttf', 40)
    draw.text( (20, 20) ,str(text), (0,0,0), font=font)

    im.save(img+'-text.jpg')

#imcar(sys.argv[1])
#changedim(sys.argv[1])
#compression(sys.argv[1])
#changeformat(sys.argv[1])
#delete4bits(sys.argv[1])
#changecolor(sys.argv[1])
#negcolor(sys.argv[1])
#cinza(sys.argv[1])
#gray(sys.argv[1])
#effect_intensity(sys.argv[1], 2)
#gama(sys.argv[1], 2)
#satur(sys.argv[1], 0.5)
#sepia(sys.argv[1])
#edgedetector(sys.argv[1])
#vignette(sys.argv[1])
#marcaagua(sys.argv[1], sys.argv[2], 0.8)
#marcaaguainvisivel(sys.argv[1], sys.argv[2])
#revelarmarcainvisivel(sys.argv[1])
#text(sys.argv[1], sys.argv[2])