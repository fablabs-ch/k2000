/*
 * This script runs in ImageJ (https://imagej.nih.gov/ij/index.html) 
 * 
 * Asks you a csv, 
 * re-print it within the imagej log to a json 'like' format 
 * compatible with our application for bar-o-matic
 * 
 * NB : you will have to modify ' by " ( with a text editor, ie NOTEPAD++ )
 * 
 * NB : check the columnSperator (either ; or , )
 * 
 */

print ("\\Clear")

path = File.openDialog("Select a csv file")
columnSperator = ";" ; // depending of regional parameter can be ","


// open the selected file as a string
file = File.openAsString(path)
// slipt the lines
lines=split(file,"\n") 
// first line corresponds to colums name
columnName = split(lines[0],columnSperator);

print ("{");
print ("'recipes': [");

// iterates the rows of the csv file
for (i_Line = 1 ; i_Line < lengthOf(lines) ; i_Line++){

	currentColumns=split(lines[i_Line],columnSperator); 
	print ("{");
	print ("'name':'"+currentColumns[0]+"',");
	print ("'description':'',");
	print ("'imageUrl':'',");

	if (currentColumns[1]=="x")	print("'shakeYourBody': true,");
	else print("'shakeYourBody': false,");
	
	print ("'items': [");
	// count the nbr of ingredients 
	// to write the last ingredient in the list without "," 
	ingredient_counter = 0;
	for (i_Col = 2 ; i_Col<lengthOf(currentColumns) ;i_Col++){
		if ( !isNaN(currentColumns[i_Col]))	ingredient_counter++;
	}

	// now writes each entry
	ingredient_total = ingredient_counter;
	ingredient_counter = 0;
	for (i_Col = 2 ; i_Col<lengthOf(currentColumns) ;i_Col++){
		if ( !isNaN(currentColumns[i_Col])){
			ingredient_counter++;
			print ("{");
			print("'ingredientId':'"+(i_Col-1)+"',");
			print("'ml':"+ (parseInt(currentColumns[i_Col])*10));
			
			// the last print should be without ,
			if (ingredient_counter < ingredient_total) print ("},");
			else print ("}");					
		}
	}
	// close recipe
	print ("]");

	// last or next recipe
	if (i_Line < lengthOf(lines)-1) print ("},");
	else print ("}");
}
// close recipes list	
print ("],");

// start ingredient
print ("'ingredients': [");

for (i_Col = 2 ; i_Col<lengthOf(columnName) ;i_Col++){
		
	print ("{");		
	print("'id':"+(i_Col-1)+",");
	print("'name':'"+columnName[i_Col]+"',");
	print("'type': 'TBD',");
	print("'manual': false,");		
	print("'color': 'TBD'");

	// next ingredient or last one
	if (i_Col < lengthOf(columnName)-1)	print ("},");
	else print ("}");
}
// close ingredient list
print ("]");
// end of document
print ("}");
