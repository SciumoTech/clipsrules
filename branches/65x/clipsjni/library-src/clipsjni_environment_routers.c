
#include "net_sf_clipsrules_jni_Environment.h"

#include "clipsjni_data.h"
#include "clipsjni_utilities.h"
#include "clipsjni_glue.h"

/********************************************************************/
/* Java_net_sf_clipsrules_jni_Environment_addRouter: Native         */
/*   function for the CLIPSJNI addRouter method.                    */
/*                                                                  */
/* Class:     net_sf_clipsrules_jni_Environment                     */
/* Method:    addRouter                                             */
/* Signature: (JLjava/lang/String;ILnet/sf/clipsrules/jni/Router;)Z */
/********************************************************************/
JNIEXPORT jboolean JNICALL Java_net_sf_clipsrules_jni_Environment_addRouter(
  JNIEnv *env, 
  jobject obj, 
  jlong clipsEnv, 
  jstring routerName, 
  jint priority, 
  jobject context)
  {
   int rv;
   jobject nobj;   
   const char *cRouterName = (*env)->GetStringUTFChars(env,routerName,NULL);

   void *oldContext = SetEnvironmentContext(JLongToPointer(clipsEnv),(void *) env); 
      
   nobj = (*env)->NewGlobalRef(env,context);
   
   rv = EnvAddRouterWithContext(JLongToPointer(clipsEnv),(char *) cRouterName,(int) priority,
                                QueryJNIRouter,PrintJNIRouter,GetcJNIRouter,
                                UngetcJNIRouter,ExitJNIRouter,(void *) nobj);
   
   (*env)->ReleaseStringUTFChars(env,routerName,cRouterName);

   SetEnvironmentContext(JLongToPointer(clipsEnv),oldContext); 

   return rv;
  }

/***************************************************************/
/* Java_net_sf_clipsrules_jni_Environment_deleteRouter: Native */
/*   function for the CLIPSJNI deleteRouter method.            */
/*                                                             */
/* Class:     net_sf_clipsrules_jni_Environment                */
/* Method:    deleteRouter                                     */
/* Signature: (JLjava/lang/String;)Z                           */
/***************************************************************/
JNIEXPORT jboolean JNICALL Java_net_sf_clipsrules_jni_Environment_deleteRouter(
  JNIEnv *env, 
  jobject obj, 
  jlong clipsEnv, 
  jstring routerName)
  {
   int rv;
   void *theCLIPSEnv = JLongToPointer(clipsEnv);
   const char *cRouterName = (*env)->GetStringUTFChars(env,routerName,NULL);
   struct router *theRouter;
   
   theRouter = EnvFindRouter(theCLIPSEnv,cRouterName);
   if (theRouter == NULL) 
     { return(0); }

   if (GetEnvironmentRouterContext(theCLIPSEnv) == theRouter->context)
     { SetEnvironmentRouterContext(theCLIPSEnv,NULL); }

   (*env)->DeleteGlobalRef(env,theRouter->context);
     
   rv = EnvDeleteRouter(theCLIPSEnv,cRouterName);
  
   (*env)->ReleaseStringUTFChars(env,routerName,cRouterName);

   return rv;
  }

/*******************************************************/
/* Java_net_sf_clipsrules_jni_Environment_printRouter  */
/* Class:     net_sf_clipsrules_jni_Environment        */
/* Method:    printRouter                              */
/* Signature: (JLjava/lang/String;Ljava/lang/String;)V */
/*******************************************************/
JNIEXPORT void JNICALL Java_net_sf_clipsrules_jni_Environment_printRouter(
  JNIEnv *env, 
  jobject obj, 
  jlong clipsEnv, 
  jstring logName, 
  jstring printString)
  {
   const char *cLogName;
   const char *cPrintString;
   void *theCLIPSEnv = JLongToPointer(clipsEnv);
   void *oldContext = SetEnvironmentContext(theCLIPSEnv,(void *) env);
   
   cLogName = (*env)->GetStringUTFChars(env,logName,NULL);
   cPrintString = (*env)->GetStringUTFChars(env,printString,NULL);

   EnvPrintRouter(theCLIPSEnv,cLogName,cPrintString);

   (*env)->ReleaseStringUTFChars(env,logName,cLogName);
   (*env)->ReleaseStringUTFChars(env,printString,cPrintString);
   
   SetEnvironmentContext(JLongToPointer(clipsEnv),oldContext);
  }

/*********************************************************/
/* Java_net_sf_clipsrules_jni_Environment_activateRouter */
/* Class:     net_sf_clipsrules_jni_Environment          */
/* Method:    activateRouter                             */
/* Signature: (JLjava/lang/String;)Z                     */
/*********************************************************/
JNIEXPORT jboolean JNICALL Java_net_sf_clipsrules_jni_Environment_activateRouter(
  JNIEnv *env, 
  jobject obj, 
  jlong clipsEnv, 
  jstring routerName)
  {
   jboolean rv;
   const char *cRouterName;
   void *theCLIPSEnv = JLongToPointer(clipsEnv);
   void *oldContext = SetEnvironmentContext(theCLIPSEnv,(void *) env);
   
   cRouterName = (*env)->GetStringUTFChars(env,routerName,NULL);

   rv = EnvActivateRouter(theCLIPSEnv,cRouterName);

   (*env)->ReleaseStringUTFChars(env,routerName,cRouterName);
   
   SetEnvironmentContext(JLongToPointer(clipsEnv),oldContext);
   
   return rv;
  }

/***********************************************************/
/* Java_net_sf_clipsrules_jni_Environment_deactivateRouter */
/* Class:     net_sf_clipsrules_jni_Environment            */
/* Method:    deactivateRouter                             */
/* Signature: (JLjava/lang/String;)Z                       */
/***********************************************************/
JNIEXPORT jboolean JNICALL Java_net_sf_clipsrules_jni_Environment_deactivateRouter(
  JNIEnv *env, 
  jobject obj, 
  jlong clipsEnv, 
  jstring routerName)
  {
   jboolean rv;
   const char *cRouterName;
   void *theCLIPSEnv = JLongToPointer(clipsEnv);
   void *oldContext = SetEnvironmentContext(theCLIPSEnv,(void *) env);
   
   cRouterName = (*env)->GetStringUTFChars(env,routerName,NULL);

   rv = EnvDeactivateRouter(theCLIPSEnv,cRouterName);

   (*env)->ReleaseStringUTFChars(env,routerName,cRouterName);
   
   SetEnvironmentContext(JLongToPointer(clipsEnv),oldContext);
   
   return rv;
  }
