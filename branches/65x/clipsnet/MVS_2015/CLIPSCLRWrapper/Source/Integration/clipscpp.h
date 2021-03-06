#pragma once
#include <string>
#include <iostream>
#include <vector>

namespace CLIPS
{

enum CLIPSType 
  { UNKNOWN_TYPE,
    FLOAT_TYPE, 
    INTEGER_TYPE, 
    SYMBOL_TYPE, 
    STRING_TYPE, 
    MULTIFIELD_TYPE, 
    EXTERNAL_ADDRESS_TYPE, 
    FACT_ADDRESS_TYPE, 
    INSTANCE_ADDRESS_TYPE, 
    INSTANCE_NAME_TYPE, 
    VOID_TYPE };

class CLIPSCPPRouter;

class DataObject;
class FactAddressValue;

class CLIPSCPPEnv
  {
   private:
      void *theEnv;

   public:
      CLIPSCPPEnv();
      ~CLIPSCPPEnv();
      void CommandLoop();
      void CommandLoopOnceThenBatch();
      void Clear();
      int GetHaltExecution();
      void SetHaltExecution(int);
      int GetEvaluationError();
      void SetEvaluationError(int);
      int GetHaltRules();
      void SetHaltRules(int);
      int ChangeDirectory(char *);
      int Load(char *);
      void LoadFromString(char *);
      void Reset();
      long long Run(long long runLimit = -1);
      int Watch(char *);
      int Unwatch(char *);
      DataObject Eval(char *);
      bool Build(char *);
      FactAddressValue *AssertString(char *);
      int AddRouter(char *,int,CLIPSCPPRouter *);
      int DeleteRouter(char *);
      size_t InputBufferCount();
      const char *GetInputBuffer();
      void SetInputBuffer(const char *);
      bool InputBufferContainsCommand();
      void PrintBanner();
      void PrintPrompt();
  };

class CLIPSCPPRouter
  {
   public:
      virtual int Query(CLIPSCPPEnv *,const char *);
      virtual int Print(CLIPSCPPEnv *,const char *,const char *);
      virtual int Getc(CLIPSCPPEnv *,const char *);
      virtual int Ungetc(CLIPSCPPEnv *,int,const char *);
      virtual int Exit(CLIPSCPPEnv *,int);

      const static char *STANDARD_OUTPUT;
      const static char *STANDARD_INPUT;
      const static char *WARNING;
      const static char *ERROR;
      const static char *TRACE;
      const static char *DIALOG;
      const static char *PROMPT;
      const static char *DISPLAY;
  };
  
class Value
  {
   public:
     Value();
     Value(const Value& v);
     virtual ~Value();
     /* virtual Value& operator= (const Value& v); */
     friend std::ostream& operator<< (std::ostream& o, const Value& s);
     friend std::ostream& operator<< (std::ostream& o, const Value* s);
     virtual std::ostream& print(std::ostream& o) const = 0;
     virtual Value *clone() const = 0; 
	 virtual CLIPSType GetCLIPSType();
  };

class VoidValue : public Value
  {  
   public:
     VoidValue();
     VoidValue(const VoidValue& v);
     virtual ~VoidValue();
     /* virtual VoidValue& operator= (const VoidValue& s); */
     virtual std::ostream& print(std::ostream& o) const;
     virtual VoidValue *clone() const; 
	 CLIPSType GetCLIPSType();
  };

class StringValue : public Value
  {  
   public:
     StringValue();
     StringValue(const char *);
     StringValue(const StringValue& v);
     virtual ~StringValue();
     /* virtual StringValue& operator= (const StringValue& v); */
     virtual std::ostream& print(std::ostream& o) const;
     virtual StringValue *clone() const; 
	 CLIPSType GetCLIPSType();
	 std::string *GetStringValue();

   private:
     std::string theString;
  };

class SymbolValue : public Value
  { 
   public:
     SymbolValue();
     SymbolValue(const char *);
     SymbolValue(const SymbolValue& v);
     virtual ~SymbolValue();
     /* virtual SymbolValue& operator= (const SymbolValue& v); */
     virtual std::ostream& print(std::ostream& o) const;
     virtual SymbolValue *clone() const; 
	 CLIPSType GetCLIPSType();
	 std::string *GetSymbolValue();
  
   private:
     std::string theString;
  };

class InstanceNameValue : public Value
  { 
   public:
     InstanceNameValue();
     InstanceNameValue(const char *);
     InstanceNameValue(const InstanceNameValue& v);
     virtual ~InstanceNameValue();
     /* virtual InstanceNameValue& operator= (const InstanceNameValue& v); */
     virtual std::ostream& print(std::ostream& o) const;
     virtual InstanceNameValue *clone() const; 
	 CLIPSType GetCLIPSType();
	 std::string *GetInstanceNameValue();
  
   private:
     std::string theString;
  };

class IntegerValue : public Value
  { 
   public:
     IntegerValue();
     IntegerValue(long long);
     IntegerValue(const IntegerValue& v);
     virtual ~IntegerValue();
     /* virtual IntegerValue& operator= (const IntegerValue& v); */
     virtual std::ostream& print(std::ostream& o) const;
     virtual IntegerValue *clone() const; 
	 CLIPSType GetCLIPSType();
	 long long GetIntegerValue();
	 double GetFloatValue();
  
   private:
     long long theInteger;
  };

class FloatValue : public Value
  { 
   public:
     FloatValue();
     FloatValue(double);
     FloatValue(const FloatValue& v);
     virtual ~FloatValue();
     virtual std::ostream& print(std::ostream& o) const;
     virtual FloatValue *clone() const; 
     CLIPSType GetCLIPSType();
     long long GetIntegerValue();
     double GetFloatValue();
  
   private:
     double theFloat;
  };

class FactAddressValue : public Value
  { 
   public:
     FactAddressValue(void *,void *);
     FactAddressValue(const FactAddressValue& v);
     virtual ~FactAddressValue();
     virtual FactAddressValue& operator= (const FactAddressValue& v);
     virtual std::ostream& print(std::ostream& o) const;
     virtual FactAddressValue *clone() const; 
     virtual DataObject GetFactSlot(char *) const;
     CLIPSType GetCLIPSType();
     virtual long long GetFactIndex() const;
     void *GetFactAddressValue();
  
   private:
     void *theEnvironment;
     void *theFactAddress;
  };
 
class InstanceAddressValue : public Value
  { 
   public:
     InstanceAddressValue(void *,void *);
     InstanceAddressValue(const InstanceAddressValue& v);
     virtual ~InstanceAddressValue();
     virtual InstanceAddressValue& operator= (const InstanceAddressValue& v);
     virtual std::ostream& print(std::ostream& o) const;
     virtual InstanceAddressValue *clone() const; 
     CLIPSType GetCLIPSType();
     virtual const char *GetInstanceName() const;
     virtual DataObject DirectGetSlot(char *) const;
     void *GetInstanceAddressValue();
  
   private:
     void *theEnvironment;
     void *theInstanceAddress;
  };
  
class MultifieldValue : public Value
  {  
   public:
     MultifieldValue();
     MultifieldValue(size_t);
     MultifieldValue(const MultifieldValue& v);
     virtual ~MultifieldValue();
     virtual MultifieldValue& operator= (const MultifieldValue& v);
     virtual std::ostream& print(std::ostream& o) const;
     virtual MultifieldValue *clone() const; 
     void add(Value *);
	 CLIPSType GetCLIPSType();
	 std::vector<Value *> *GetMultifieldValue();

   private:
     std::vector<Value *> theMultifield;
  };

class DataObject
  {
   public:
     DataObject();
     DataObject(Value *v);
     DataObject(const DataObject& v);
     virtual ~DataObject();
     virtual DataObject& operator= (const DataObject& s);
     friend std::ostream& operator<< (std::ostream& o, const DataObject& s);
     friend std::ostream& operator<< (std::ostream& o, const DataObject* s);
     virtual std::ostream& print(std::ostream& o) const;
	 CLIPSType GetCLIPSType();
	 Value *GetCLIPSValue();
     static DataObject Void();
     static DataObject String();
     static DataObject String(char *);
     static DataObject Symbol();
     static DataObject Symbol(char *);
     static DataObject InstanceName();
     static DataObject InstanceName(char *);
     static DataObject Multifield();
     static DataObject Multifield(size_t);
     static DataObject Integer();
     static DataObject Integer(long long);
     static DataObject Float();
     static DataObject Float(double);
     static DataObject FactAddress(void *,void *);
     static DataObject InstanceAddress(void *,void *);

   private:
     Value *theValue;
  };

inline DataObject DataObject::Void()
  { return DataObject(); }

inline DataObject DataObject::String()
  { return DataObject(new StringValue()); }

inline DataObject DataObject::String(
  char *initialString)
  { return DataObject(new StringValue(initialString)); }

inline DataObject DataObject::Symbol()
  { return DataObject(new SymbolValue()); }

inline DataObject DataObject::Symbol(
  char *initialString)
  { return DataObject(new SymbolValue(initialString)); }

inline DataObject DataObject::InstanceName()
  { return DataObject(new InstanceNameValue()); }

inline DataObject DataObject::InstanceName(
  char *initialString)
  { return DataObject(new InstanceNameValue(initialString)); }

inline DataObject DataObject::Multifield()
  { return DataObject(new MultifieldValue()); }

inline DataObject DataObject::Multifield(size_t size)
  { return DataObject(new MultifieldValue(size)); }

inline DataObject DataObject::Integer()
  { return DataObject(new IntegerValue(0)); }

inline DataObject DataObject::Integer(long long theInteger)
  { return DataObject(new IntegerValue(theInteger)); }

inline DataObject DataObject::Float()
  { return DataObject(new FloatValue(0.0)); }

inline DataObject DataObject::Float(double theFloat)
  { return DataObject(new FloatValue(theFloat)); }

inline DataObject DataObject::FactAddress(void *theEnv,void *theFact)
  { return DataObject(new FactAddressValue(theEnv,theFact)); }

inline DataObject DataObject::InstanceAddress(void *theEnv,void *theInstance)
  { return DataObject(new InstanceAddressValue(theEnv,theInstance)); }

}
