/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

public class aiString : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal aiString(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(aiString obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~aiString() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          AssimpPINVOKE.delete_aiString(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public override string ToString() { return Data; } 

  public aiString() : this(AssimpPINVOKE.new_aiString__SWIG_0(), true) {
  }

  public aiString(aiString rOther) : this(AssimpPINVOKE.new_aiString__SWIG_1(aiString.getCPtr(rOther)), true) {
    if (AssimpPINVOKE.SWIGPendingException.Pending) throw AssimpPINVOKE.SWIGPendingException.Retrieve();
  }

  public aiString(string pString) : this(AssimpPINVOKE.new_aiString__SWIG_2(pString), true) {
    if (AssimpPINVOKE.SWIGPendingException.Pending) throw AssimpPINVOKE.SWIGPendingException.Retrieve();
  }

  public aiString __set__(string sz) {
    aiString ret = new aiString(AssimpPINVOKE.aiString___set____SWIG_0(swigCPtr, sz), false);
    return ret;
  }

  public bool __equal__(aiString other) {
    bool ret = AssimpPINVOKE.aiString___equal__(swigCPtr, aiString.getCPtr(other));
    if (AssimpPINVOKE.SWIGPendingException.Pending) throw AssimpPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public bool __nequal__(aiString other) {
    bool ret = AssimpPINVOKE.aiString___nequal__(swigCPtr, aiString.getCPtr(other));
    if (AssimpPINVOKE.SWIGPendingException.Pending) throw AssimpPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint Length {
    set {
      AssimpPINVOKE.aiString_Length_set(swigCPtr, value);
    } 
    get {
      uint ret = AssimpPINVOKE.aiString_Length_get(swigCPtr);
      return ret;
    } 
  }

  public string Data {
    set {
      AssimpPINVOKE.aiString_Data_set(swigCPtr, value);
    } 
    get {
      string ret = AssimpPINVOKE.aiString_Data_get(swigCPtr);
      return ret;
    } 
  }

}
