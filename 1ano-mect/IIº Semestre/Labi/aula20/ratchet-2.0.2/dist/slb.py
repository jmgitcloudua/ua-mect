from math import radians, cos, sin, asin, sqrt
import cherrypy
import time

class HelloWorld(object):
	@cherrypy.expose
	def index(self):
		# Metodo serve_file tb poderia ser utilizado
		f = open("index.html")
		data = f.read()
		f.close()
		return data
	
	@cherrypy.expose
	def time(self):
		cherrypy.response.headers['Content-Type'] = 'application/json'
		return time.strftime('{"date":"%d-%m-%Y", "time":"%H:%M:%S"}')


@cherrypy.expose
def distance(lat, lon):
	lat1 = 38.752667
	lon1 = -9.184711
	# graus para radianos
	lon, lat, lon1, lat1 = map(radians, [lon, lat, lon1, lat1])
	
	# formula de haversine
	dlon = lon - lon1
	dlat = lat - lat1
	a = sin(dlat/2)**2 + cos(lat1) * cos(lat) * sin(dlon/2) **2
	c = 2*asin(sqrt(a))
	
	# 6367 km is the radius of the Earth
	km = 6367 * c
	
	cherrypy.response.headers['content-type'] = 'application/json'
	cherrypy.response.body = '{"distance": %d}' % km
