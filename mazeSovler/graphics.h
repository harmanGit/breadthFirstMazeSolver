bool showGraph = false;
bool solved = false;

void drawMap()
{ 
	for (int i=0; i<NUMROWS; i++)
      for (int j=0; j<NUMCOLS; j++)
	  {	
		  glBegin(GL_QUADS);
			  if ( mapArray[i][j] == LAND )
				  glColor3f(0.0,1.0,0.0);
			  else
				  glColor3f(0.0,0.0,1.0);
			  glVertex2i(j,i);
			  glVertex2i(j,i+1);
			  glVertex2i(j+1,i+1);
			  glVertex2i(j+1,i);
		  glEnd();

		  glLineWidth(1);
		  glBegin(GL_LINE_LOOP);
			  glColor3f(0.0,0.0,0.0);
			  glVertex2i(j,i);
			  glVertex2i(j,i+1);
			  glVertex2i(j+1,i+1);
			  glVertex2i(j+1,i);
		  glEnd();
	  } 
}

void drawPath( ) 
{
	glLineWidth(3);
	glColor3f(1.0,0.0,0.0);
	int i = cellsCount-1;

	while ( mapGraph.vertices[i].path != NULL )
	{  
		int row = i / NUMROWS;
		int col = i % NUMROWS;
		glBegin(GL_LINES);
			glVertex2f(col+0.5,row+0.5);

			i = mapGraph.vertices[i].path->id;
			row = i / NUMROWS;
			col = i % NUMROWS;

			glVertex2f(col+0.5,row+0.5);
		glEnd();	         
	}  

	glLineWidth(1);
	glFlush();
}

void drawGraph()
{ 
	glLineWidth(2);
	glPointSize(5);
	glColor3f(0.4,0.4,0.4);

	glBegin(GL_POINTS);
		for (int i=0; i<NUMROWS; i++)
			for (int j=0; j<NUMCOLS; j++)
				glVertex2f(j+0.5,i+0.5);  
	glEnd();

	glBegin(GL_LINES);
		for (int i=0; i<NUMROWS; i++)
			for (int j=0; j<NUMCOLS; j++)
			{	
				for (list<vertex*>::iterator itr = mapGraph.vertices[i*NUMCOLS+j].neighbors.begin();
					itr != mapGraph.vertices[i*NUMCOLS+j].neighbors.end(); itr++)
				{ 
					int nbr_id = (*itr)->id;
					int row = nbr_id / NUMCOLS;
					int col = nbr_id % NUMCOLS;
					glVertex2f(j+0.5,i+0.5);   
					glVertex2f(col+0.5,row+0.5);  
				}
			} 
		glEnd();
}

void display()
{	
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	drawMap();
	if (showGraph) drawGraph();
	if (solved) drawPath();
	glFlush();
}

void mouse(int btn, int state, int x, int y)
{
	if (btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (!showGraph)
		{
			showGraph = true;
			solved = false;
		}
		else
		{
			showGraph = false;
			findAndPrintPath();
			solved = true;
		}
		glutPostRedisplay();
	}
}

void startGraphicsLoop(int argc, char** argv)
{
	// These are the GLUT functions to set up the window and main loop
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(700,700);
	glutInitWindowPosition(5,5);
	glutCreateWindow("Path Finder");

	// set up viewing mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1,NUMCOLS+1,NUMROWS+1,-1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// set up event handlers
	glutDisplayFunc(display);
	glutMouseFunc(mouse);

	glutMainLoop();
}