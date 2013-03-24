#include "../headers/framework.h"

const double Framework::FRAME_TIME = 1.0 / Framework::FPS * 1000.0;

Framework *Framework::instance = NULL;

Framework::Framework() {
    fullScreen = false;
    title = "GLUT";
}

Framework::~Framework() {}

void Framework::startFramework(int argc, char *argv[]) {
    setInstance();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);
    glutInitWindowPosition(WINDOW_X_POSITION, WINDOW_Y_POSITION);
    if(fullScreen)
        glutFullScreen();
    else
        glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow(title.c_str());
	
    #ifdef FRAMEWORK_USE_GLEW
    		/******GLEW START*******/
    		GLenum err = glewInit();
    		if (GLEW_OK != err)
    		{
    		  /* Problem: glewInit failed, something is seriously wrong. */
    		  cout << "Error: " << glewGetErrorString(err) << endl;
    		}
    		cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << endl;
    		/******GLEW END*******/
    #endif
	
    glutDisplayFunc(displayWrapper);
    glutReshapeFunc(reshapeWrapper);
    glutKeyboardFunc(keyboardWrapper);
    glutSpecialFunc(specialWrapper);
    glutMouseFunc(mouseWrapper);
    glutTimerFunc(FPS/3, timeWrapper, 0);
    glutIdleFunc(runWrapper);

    init();
    glutMainLoop();
}

void Framework::setInstance() {instance = this;}
void Framework::setInstance(Framework * framework) {instance = framework;}
Framework* Framework::getInstance() {return instance;}
void Framework::setFullScreen(GLboolean option) {fullScreen = option;}
void Framework::setTitle(string title) {this->title = title;}

void Framework::init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    load();
}

void Framework::run() {
    if(frameRateTimer.isStopped()) {	// The initial frame has the timer stopped, start it once
        frameRateTimer.start();
    }

    frameRateTimer.stop();			// stop the timer and calculate time since last frame
    double milliseconds = frameRateTimer.getElapsedMilliseconds();
    frameTimeElapsed += milliseconds;

    if( frameTimeElapsed >= FRAME_TIME ) {	// If the time exceeds a certain "frame rate" then show the next frame
        glutPostRedisplay();
        frameTimeElapsed -= FRAME_TIME;		// remove a "frame" and start counting up again
    }
    frameRateTimer.start();
}


/******************************************/
/*  START VIRTUAL FUNCTIONS TO OVERWRITE  */
/******************************************/


void Framework::display() {}

void Framework::reshape(GLint width, GLint height) {}

void Framework::keyboard(GLubyte key, GLint x, GLint y){}

void Framework::special(GLint key, GLint x, GLint y){}

void Framework::mouse(GLsizei button, GLsizei state, GLsizei x, GLsizei y) {}

void Framework::load() {}

void Framework::time(GLint value) {}


/******************************************/
/*  END VIRTUAL FUNCTIONS TO OVERWRITE    */
/******************************************/



/******************************************/
/*  START WRAPPERS FUNCTIONS TO GLUT      */
/******************************************/


void Framework::displayWrapper() {
    instance->display();
}

void Framework::runWrapper() {
    instance->run();
}

void Framework::reshapeWrapper(GLint width, GLint height) {
    instance->reshape(width, height);
}

void Framework::keyboardWrapper(GLubyte key, GLint x, GLint y) {
    instance->keyboard(key,x,y);
}

void Framework::specialWrapper(GLint key, GLint x, GLint y) {
    instance->special(key,x,y);
}

void Framework::mouseWrapper(GLsizei button, GLsizei state, GLsizei x, GLsizei y) {
    instance->mouse(button, state, x, y);
}

void Framework::timeWrapper(GLint value) {
    instance->time(value);
    glutTimerFunc(FPS/3, timeWrapper, 0);
}


/******************************************/
/*  END WRAPPERS FUNCTIONS TO GLUT        */
/******************************************/
