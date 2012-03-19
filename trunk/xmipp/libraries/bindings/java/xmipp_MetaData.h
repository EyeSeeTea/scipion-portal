/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class xmipp_MetaData */

#ifndef _Included_xmipp_jni_MetaData
#define _Included_xmipp_jni_MetaData
#ifdef __cplusplus
extern "C" {
#endif
#undef xmipp_MetaData_MD_OVERWRITE
#define xmipp_MetaData_MD_OVERWRITE 0L
#undef xmipp_MetaData_MD_APPEND
#define xmipp_MetaData_MD_APPEND 1L
/*
 * Class:     xmipp_MetaData
 * Method:    create
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_MetaData_create
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_MetaData
 * Method:    destroy
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_MetaData_destroy
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_MetaData
 * Method:    read_
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_MetaData_read_1
  (JNIEnv *, jobject, jstring);

/*
 * Class:     xmipp_MetaData
 * Method:    size
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_xmipp_jni_MetaData_size
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_MetaData
 * Method:    setColumnFormat
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_MetaData_setColumnFormat
  (JNIEnv *, jobject, jboolean);

/*
 * Class:     xmipp_MetaData
 * Method:    write
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_MetaData_write
  (JNIEnv *, jobject, jstring);

/*
 * Class:     xmipp_MetaData
 * Method:    writeBlock
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_MetaData_writeBlock
  (JNIEnv *, jobject, jstring);

/*
 * Class:     xmipp_MetaData
 * Method:    print
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_MetaData_print
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_MetaData
 * Method:    containsLabel
 * Signature: (V)Z
 */
JNIEXPORT jboolean JNICALL Java_xmipp_jni_MetaData_isColumnFormat
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_MetaData
 * Method:    containsLabel
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_xmipp_jni_MetaData_containsLabel
  (JNIEnv *, jobject, jint);

/*
 * Class:     xmipp_MetaData
 * Method:    label2Str
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_xmipp_jni_MetaData_label2Str
  (JNIEnv *, jclass, jint);

/*
 * Class:     xmipp_MetaData
 * Method:    label2Str
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jint JNICALL Java_xmipp_jni_MetaData_str2Label
  (JNIEnv *, jclass, jstring);

/*
 * Class:     xmipp_MetaData
 * Method:    getBlocksInMetaDataFile
 * Signature: (Ljava/lang/String;)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_xmipp_jni_MetaData_getBlocksInMetaDataFile
  (JNIEnv *, jclass, jstring);

/*
 * Class:     xmipp_MetaData
 * Method:    getActiveLabels
 * Signature: ()[I
 */
JNIEXPORT jintArray JNICALL Java_xmipp_jni_MetaData_getActiveLabels
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_MetaData
 * Method:    getLabelType
 * Signature: (I)Ljava/lang/Class;
 */
JNIEXPORT jint JNICALL Java_xmipp_jni_MetaData_getLabelType
  (JNIEnv *, jclass, jint);

/*
 * Class:     xmipp_MetaData
 * Method:    isTextFile
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_xmipp_jni_MetaData_isTextFile
  (JNIEnv *, jclass, jint);

/*
 * Class:     xmipp_MetaData
 * Method:    isMetadata
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_xmipp_jni_MetaData_isMetadata
  (JNIEnv *, jclass, jint);

/*
 * Class:     xmipp_MetaData
 * Method:    isCtfParam
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_xmipp_jni_MetaData_isCtfParam
  (JNIEnv *, jclass, jint);

/*
 * Class:     xmipp_MetaData
 * Method:    isImage
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_xmipp_jni_MetaData_isImage
  (JNIEnv *, jclass, jint);

/*
 * Class:     xmipp_MetaData
 * Method:    isStack
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_xmipp_jni_MetaData_isStack
  (JNIEnv *, jclass, jint);

/*
 * Class:     xmipp_MetaData
 * Method:    isMicrograph
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_xmipp_jni_MetaData_isMicrograph
  (JNIEnv *, jclass, jint);

/*
 * Class:     xmipp_MetaData
 * Method:    isPSD
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_xmipp_jni_MetaData_isPSD
  (JNIEnv *, jclass, jint);

/*
 * Class:     xmipp_MetaData
 * Method:    isMetadataFile
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_xmipp_jni_MetaData_isMetadataFile
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_MetaData
 * Method:    makeAbsPath
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_MetaData_makeAbsPath
  (JNIEnv *, jobject, jint);

/*
 * Class:     xmipp_MetaData
 * Method:    getValueInt
 * Signature: (IJ)I
 */
JNIEXPORT jint JNICALL Java_xmipp_jni_MetaData_getValueInt
  (JNIEnv *, jobject, jint, jlong);

/*
 * Class:     xmipp_MetaData
 * Method:    getValueLong
 * Signature: (IJ)J
 */
JNIEXPORT jlong JNICALL Java_xmipp_jni_MetaData_getValueLong
  (JNIEnv *, jobject, jint, jlong);

/*
 * Class:     xmipp_MetaData
 * Method:    getValueDouble
 * Signature: (IJ)D
 */
JNIEXPORT jdouble JNICALL Java_xmipp_jni_MetaData_getValueDouble
  (JNIEnv *, jobject, jint, jlong);

/*
 * Class:     xmipp_MetaData
 * Method:    getValueString
 * Signature: (IJ)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_xmipp_jni_MetaData_getValueString
  (JNIEnv *, jobject, jint, jlong);

/*
 * Class:     xmipp_MetaData
 * Method:    getValueBoolean
 * Signature: (IJ)Z
 */
JNIEXPORT jboolean JNICALL Java_xmipp_jni_MetaData_getValueBoolean
  (JNIEnv *, jobject, jint, jlong);

/*
 * Class:     xmipp_MetaData
 * Method:    getStatistics
 * Signature: (Z)[D
 */
JNIEXPORT jdoubleArray JNICALL Java_xmipp_jni_MetaData_getStatistics
  (JNIEnv *, jobject, jboolean);

/*
 * Class:     xmipp_MetaData
 * Method:    getColumnValues
 * Signature: (I)[D
 */
JNIEXPORT jdoubleArray JNICALL Java_xmipp_jni_MetaData_getColumnValues
  (JNIEnv *, jobject, jint);

/*
 * Class:     xmipp_MetaData
 * Method:    setValueInt
 * Signature: (IIJ)Z
 */
JNIEXPORT jboolean JNICALL Java_xmipp_jni_MetaData_setValueInt
  (JNIEnv *, jobject, jint, jint, jlong);

/*
 * Class:     xmipp_MetaData
 * Method:    setValueDouble
 * Signature: (IDJ)Z
 */
JNIEXPORT jboolean JNICALL Java_xmipp_jni_MetaData_setValueDouble
  (JNIEnv *, jobject, jint, jdouble, jlong);

/*
 * Class:     xmipp_MetaData
 * Method:    setValueString
 * Signature: (ILjava/lang/String;J)Z
 */
JNIEXPORT jboolean JNICALL Java_xmipp_jni_MetaData_setValueString
  (JNIEnv *, jobject, jint, jstring, jlong);

/*
 * Class:     xmipp_MetaData
 * Method:    setValueBoolean
 * Signature: (IZJ)Z
 */
JNIEXPORT jboolean JNICALL Java_xmipp_jni_MetaData_setValueBoolean
  (JNIEnv *, jobject, jint, jboolean, jlong);

/*
 * Class:     xmipp_MetaData
 * Method:    findObjects
 * Signature: ()[J
 */
JNIEXPORT jlongArray JNICALL Java_xmipp_jni_MetaData_findObjects
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_MetaData
 * Method:    findObjects
 * Signature: ()[J
 */
JNIEXPORT void JNICALL Java_xmipp_jni_MetaData_sort
  (JNIEnv *, jobject, jint, jboolean);

/*
 * Class:     xmipp_MetaData
 * Method:    importObjects
 * Signature: (Lxmipp/MetaData;[J)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_MetaData_importObjects
  (JNIEnv *, jobject, jobject, jlongArray);

/*
 * Class:     xmipp_MetaData
 * Method:    firstObject
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_xmipp_jni_MetaData_firstObject
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_MetaData
 * Method:    addObject
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_xmipp_jni_MetaData_addObject
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_MetaData
 * Method:    addLabel
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_MetaData_addLabel
  (JNIEnv *, jobject, jint);

/*
 * Class:     xmipp_MetaData
 * Method:    getPCAbasis
 * Signature: (Lxmipp/ImageGeneric;)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_MetaData_getStatsImages
  (JNIEnv *, jobject, jobject, jobject, jboolean, jint);


/*
 * Class:     xmipp_MetaData
 * Method:    getPCAbasis
 * Signature: (Lxmipp/ImageGeneric;)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_MetaData_getPCAbasis
  (JNIEnv *, jobject, jobject, jint);

/*
 * Class:     xmipp_MetaData
 * Method:    computeFourierStatistics
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_MetaData_computeFourierStatistics
  (JNIEnv *, jobject, jobject, jint);

/*
 * Class:     xmipp_MetaData
 * Method:    enableDebug
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_MetaData_enableDebug
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_MetaData
 * Method:    readPlain
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_MetaData_readPlain
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     xmipp_MetaData
 * Method:    writeImages
 */
JNIEXPORT void JNICALL Java_xmipp_jni_MetaData_writeImages
  (JNIEnv *, jobject, jstring, jboolean, jint);

#ifdef __cplusplus
}
#endif
#endif
