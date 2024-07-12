var lat = 0;
var lon = 0;

jQuery(document).ready(function($) {
						navigator.geolocation.getCurrentPosition(function(position) {
							lat = position.coords.latitude;
							lon = position.coords.longitude;
						});
				});
				
var map = new L.Map("map", {center: [0, 0],zoom: 15});

var osmUrl="http://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png";
var osmAttrib="Map data OpenStreetMap contributors";
var osm = new L.TileLayer(osmUrl, {attribution: osmAttrib});

map.addLayer(osm);