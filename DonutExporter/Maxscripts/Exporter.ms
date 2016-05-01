-- Here is the data you must specify thus you can properly export your scene
arg_outputDirectory = "C:/TEMP"
arg_projectName = "defaultProject"
arg_levelName = "defaultFlour"
arg_commonAssetFolder = "D:/Git/External/Donut/assets"

(
	local geometryArray =  geometry as array
	ExportForDonut arg_outputDirectory arg_projectName arg_levelName geometryArray 
)