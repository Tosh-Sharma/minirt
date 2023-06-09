# minirt

### Content of 'sudo code' file
Read once thr whole file, increment ints for A, C, L etc as they come up, close the file
array of ints which represents the numlber of times one specific object is mentionned
then malloc "int" amount of time for each object example : scene.light = (t_light)malloc(sizeof(t_light) * t_light_count)
then store the data in those storage malloced tables => Read a second time with parser function
	for each object it finds run example : rt->ambient[position_index] = ambient_lightning(rt);
	position index will be increased after ambiant light is done so that next time it finds A, it will be storing in the second array of rt->ambient

Step one
PC looks at the data and apply math to understand which set of (x,y,z) are part of the object.
Each (x,y,z) point will be a struct like this 
t_point 
{
	t_vector	coords;
	t_color		color;
}
Step two
Sends rays throught the scene and the first one it touches will be printed in 2D with math calculation,
	because like the picture, behind the pc screen, the down of the bag pack doesnt exist in the final rendering
Each points in the scene is either nothing, or is an object. From the moment we understand which is behind what, we can free all of the useless data and then start rendering the remaining