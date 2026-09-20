# How parcelling will work

## Tile Terrain Generation

### The map

A giant world plane is created, roughly 5,000km^2 and subdived into 4-8 sided 
areas approximately 5km^2 in area. The game starts with about 25km^2 already 
unlocked and generated, the rest is covered in fog and will be generated when 
the player expands.

### The Mesh

 - A 5km^2 map subdivision is subdivied into a trianglular mesh
 - Randomly pair adjacent triangles and remove their shared edges, producing a 
 mixture of quads and triangles
 - Subdivide every face into quads:
    - A triangle becomes three quads
    - An existing quad becomes four quads
 - Relax the verticies iteratively so cells approach similar areas and roughly 
 square proportions
 - Perlin noise or other terrain height map generator vertically deform the terrain

### Ground type

A simple perlin noise layer will be used to set ground types and minerals.

### Hydrology

The map will have a rain based hydrological model applied to it. This will form
rivers, ponds, lakes and flood plains. Previous ground types will be used to
evaluate the areas water absorbtion. The game will rerun this model as the map 
changes throughout the game. This means that building a giant car park with 
poor drainage will cause flooding. Largely this will be done via rain 
simmulation, areas that collect water at say 20% rainfall will become permenant
terrain features. Extreme weather will form part of the game, rivers will flood
and overflow their banks.

### The Biome

Wave function collapse is used to determine the biome. It will take into 
account elevation, hydrology (moisture, distance to river etc.), slope, 
adjacent biomes and other terrain aspects to create biome areas.

### The Nature Overlay

If we took all these attributes and created an overlay what would we see. We 
would see the a map divided into biome segments and geographical features such 
as rivers.

## Parcel Generation

Boime edges and water features will form the outline of parcels before any 
manmade features are added. Field/plains biomes that have sutable soil types 
will get subdivided and created into fields, these fields need access and so 
easements will be created to provide access. Most other biomes will simply have
a maximum area restriction to prevent overly large parcels.

## References

 - https://boristhebrave.com/docs/sylves/1/articles/tutorials/townscaper.html