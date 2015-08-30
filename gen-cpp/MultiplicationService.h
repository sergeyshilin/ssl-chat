/**
 * Autogenerated by Thrift Compiler (1.0.0-dev)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef MultiplicationService_H
#define MultiplicationService_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "test_types.h"

namespace test {

#ifdef _WIN32
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class MultiplicationServiceIf {
 public:
  virtual ~MultiplicationServiceIf() {}

  /**
   * A method definition looks like C code. It has a return type, arguments,
   * and optionally a list of exceptions that it may throw. Note that argument
   * lists and exception lists are specified using the exact same syntax as
   * field lists in struct or exception definitions.
   */
  virtual void ping() = 0;
  virtual int32_t add(const int32_t num1, const int32_t num2) = 0;
};

class MultiplicationServiceIfFactory {
 public:
  typedef MultiplicationServiceIf Handler;

  virtual ~MultiplicationServiceIfFactory() {}

  virtual MultiplicationServiceIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(MultiplicationServiceIf* /* handler */) = 0;
};

class MultiplicationServiceIfSingletonFactory : virtual public MultiplicationServiceIfFactory {
 public:
  MultiplicationServiceIfSingletonFactory(const boost::shared_ptr<MultiplicationServiceIf>& iface) : iface_(iface) {}
  virtual ~MultiplicationServiceIfSingletonFactory() {}

  virtual MultiplicationServiceIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(MultiplicationServiceIf* /* handler */) {}

 protected:
  boost::shared_ptr<MultiplicationServiceIf> iface_;
};

class MultiplicationServiceNull : virtual public MultiplicationServiceIf {
 public:
  virtual ~MultiplicationServiceNull() {}
  void ping() {
    return;
  }
  int32_t add(const int32_t /* num1 */, const int32_t /* num2 */) {
    int32_t _return = 0;
    return _return;
  }
};


class MultiplicationService_ping_args {
 public:

  MultiplicationService_ping_args(const MultiplicationService_ping_args&);
  MultiplicationService_ping_args& operator=(const MultiplicationService_ping_args&);
  MultiplicationService_ping_args() {
  }

  virtual ~MultiplicationService_ping_args() throw();

  bool operator == (const MultiplicationService_ping_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const MultiplicationService_ping_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MultiplicationService_ping_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const MultiplicationService_ping_args& obj);

};


class MultiplicationService_ping_pargs {
 public:


  virtual ~MultiplicationService_ping_pargs() throw();

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const MultiplicationService_ping_pargs& obj);

};


class MultiplicationService_ping_result {
 public:

  MultiplicationService_ping_result(const MultiplicationService_ping_result&);
  MultiplicationService_ping_result& operator=(const MultiplicationService_ping_result&);
  MultiplicationService_ping_result() {
  }

  virtual ~MultiplicationService_ping_result() throw();

  bool operator == (const MultiplicationService_ping_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const MultiplicationService_ping_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MultiplicationService_ping_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const MultiplicationService_ping_result& obj);

};


class MultiplicationService_ping_presult {
 public:


  virtual ~MultiplicationService_ping_presult() throw();

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

  friend std::ostream& operator<<(std::ostream& out, const MultiplicationService_ping_presult& obj);

};

typedef struct _MultiplicationService_add_args__isset {
  _MultiplicationService_add_args__isset() : num1(false), num2(false) {}
  bool num1 :1;
  bool num2 :1;
} _MultiplicationService_add_args__isset;

class MultiplicationService_add_args {
 public:

  MultiplicationService_add_args(const MultiplicationService_add_args&);
  MultiplicationService_add_args& operator=(const MultiplicationService_add_args&);
  MultiplicationService_add_args() : num1(0), num2(0) {
  }

  virtual ~MultiplicationService_add_args() throw();
  int32_t num1;
  int32_t num2;

  _MultiplicationService_add_args__isset __isset;

  void __set_num1(const int32_t val);

  void __set_num2(const int32_t val);

  bool operator == (const MultiplicationService_add_args & rhs) const
  {
    if (!(num1 == rhs.num1))
      return false;
    if (!(num2 == rhs.num2))
      return false;
    return true;
  }
  bool operator != (const MultiplicationService_add_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MultiplicationService_add_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const MultiplicationService_add_args& obj);

};


class MultiplicationService_add_pargs {
 public:


  virtual ~MultiplicationService_add_pargs() throw();
  const int32_t* num1;
  const int32_t* num2;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const MultiplicationService_add_pargs& obj);

};

typedef struct _MultiplicationService_add_result__isset {
  _MultiplicationService_add_result__isset() : success(false) {}
  bool success :1;
} _MultiplicationService_add_result__isset;

class MultiplicationService_add_result {
 public:

  MultiplicationService_add_result(const MultiplicationService_add_result&);
  MultiplicationService_add_result& operator=(const MultiplicationService_add_result&);
  MultiplicationService_add_result() : success(0) {
  }

  virtual ~MultiplicationService_add_result() throw();
  int32_t success;

  _MultiplicationService_add_result__isset __isset;

  void __set_success(const int32_t val);

  bool operator == (const MultiplicationService_add_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const MultiplicationService_add_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const MultiplicationService_add_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const MultiplicationService_add_result& obj);

};

typedef struct _MultiplicationService_add_presult__isset {
  _MultiplicationService_add_presult__isset() : success(false) {}
  bool success :1;
} _MultiplicationService_add_presult__isset;

class MultiplicationService_add_presult {
 public:


  virtual ~MultiplicationService_add_presult() throw();
  int32_t* success;

  _MultiplicationService_add_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

  friend std::ostream& operator<<(std::ostream& out, const MultiplicationService_add_presult& obj);

};

class MultiplicationServiceClient : virtual public MultiplicationServiceIf {
 public:
  MultiplicationServiceClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  MultiplicationServiceClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void ping();
  void send_ping();
  void recv_ping();
  int32_t add(const int32_t num1, const int32_t num2);
  void send_add(const int32_t num1, const int32_t num2);
  int32_t recv_add();
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class MultiplicationServiceProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<MultiplicationServiceIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (MultiplicationServiceProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_ping(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_add(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  MultiplicationServiceProcessor(boost::shared_ptr<MultiplicationServiceIf> iface) :
    iface_(iface) {
    processMap_["ping"] = &MultiplicationServiceProcessor::process_ping;
    processMap_["add"] = &MultiplicationServiceProcessor::process_add;
  }

  virtual ~MultiplicationServiceProcessor() {}
};

class MultiplicationServiceProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  MultiplicationServiceProcessorFactory(const ::boost::shared_ptr< MultiplicationServiceIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< MultiplicationServiceIfFactory > handlerFactory_;
};

class MultiplicationServiceMultiface : virtual public MultiplicationServiceIf {
 public:
  MultiplicationServiceMultiface(std::vector<boost::shared_ptr<MultiplicationServiceIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~MultiplicationServiceMultiface() {}
 protected:
  std::vector<boost::shared_ptr<MultiplicationServiceIf> > ifaces_;
  MultiplicationServiceMultiface() {}
  void add(boost::shared_ptr<MultiplicationServiceIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void ping() {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->ping();
    }
    ifaces_[i]->ping();
  }

  int32_t add(const int32_t num1, const int32_t num2) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->add(num1, num2);
    }
    return ifaces_[i]->add(num1, num2);
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class MultiplicationServiceConcurrentClient : virtual public MultiplicationServiceIf {
 public:
  MultiplicationServiceConcurrentClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  MultiplicationServiceConcurrentClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void ping();
  int32_t send_ping();
  void recv_ping(const int32_t seqid);
  int32_t add(const int32_t num1, const int32_t num2);
  int32_t send_add(const int32_t num1, const int32_t num2);
  int32_t recv_add(const int32_t seqid);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  ::apache::thrift::async::TConcurrentClientSyncInfo sync_;
};

#ifdef _WIN32
  #pragma warning( pop )
#endif

} // namespace

#endif
