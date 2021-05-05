#include <gl/glew.h>
#include <gl/GL.h>
#include <stdio.h>

void GLAPIENTRY
MessageCallback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam )
{
    char* sevString;
    char* messageType;

    switch (severity){
    case GL_DEBUG_SEVERITY_HIGH: sevString = new char[] {"!!HIGH SEVERITY!!"}; break;
    case GL_DEBUG_SEVERITY_MEDIUM: sevString = new char[] {"Med Severity"}; break;
    case GL_DEBUG_SEVERITY_LOW: sevString = new char[] {"Low Severity"}; break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: sevString = new char[] {"Notification"}; break; }

    switch (type){
    case GL_DEBUG_TYPE_ERROR: messageType = new char[] {"Error"}; break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: messageType = new char[] {"Deprecated"}; break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: messageType = new char[] {"Undefined Behaviour"}; break;
    case GL_DEBUG_TYPE_PERFORMANCE: messageType = new char[] {"Performance Issue"}; break;
    default: messageType = new char[] {"Other"}; break; }

    printf("OpenGl %s (%d): %s - %s\n\n", messageType, id, sevString, message);
}

void StartGLDebug()
{
    glDebugMessageCallback(MessageCallback, 0); 
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
}