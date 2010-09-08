/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


public final class DataType {
  public final static DataType Unknown_Type = new DataType("Unknown_Type", XmippDataJNI.Unknown_Type_get());
  public final static DataType UChar = new DataType("UChar", XmippDataJNI.UChar_get());
  public final static DataType SChar = new DataType("SChar", XmippDataJNI.SChar_get());
  public final static DataType UShort = new DataType("UShort", XmippDataJNI.UShort_get());
  public final static DataType Short = new DataType("Short", XmippDataJNI.Short_get());
  public final static DataType UInt = new DataType("UInt", XmippDataJNI.UInt_get());
  public final static DataType Int = new DataType("Int", XmippDataJNI.Int_get());
  public final static DataType Long = new DataType("Long", XmippDataJNI.Long_get());
  public final static DataType Float = new DataType("Float", XmippDataJNI.Float_get());
  public final static DataType Double = new DataType("Double", XmippDataJNI.Double_get());
  public final static DataType ComplexShort = new DataType("ComplexShort", XmippDataJNI.ComplexShort_get());
  public final static DataType ComplexInt = new DataType("ComplexInt", XmippDataJNI.ComplexInt_get());
  public final static DataType ComplexFloat = new DataType("ComplexFloat", XmippDataJNI.ComplexFloat_get());
  public final static DataType ComplexDouble = new DataType("ComplexDouble", XmippDataJNI.ComplexDouble_get());
  public final static DataType Bool = new DataType("Bool", XmippDataJNI.Bool_get());

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static DataType swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + DataType.class + " with value " + swigValue);
  }

  private DataType(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private DataType(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private DataType(String swigName, DataType swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static DataType[] swigValues = { Unknown_Type, UChar, SChar, UShort, Short, UInt, Int, Long, Float, Double, ComplexShort, ComplexInt, ComplexFloat, ComplexDouble, Bool };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}

