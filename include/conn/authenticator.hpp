#ifndef AUTHENTICATOR_HPP
#define AUTHENTICATOR_HPP

#include <grpcpp/grpcpp.h>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class Authenticator : public grpc::MetadataCredentialsPlugin {
 public:
  Authenticator(const grpc::string& token, const string& certificate);
  grpc::Status GetMetadata(grpc::string_ref service_url,
                           grpc::string_ref method_name,
                           const grpc::AuthContext& channel_auth_context,
                           multimap<grpc::string, grpc::string>* metadata);
  void LoadCertificate(const string& filename);
  grpc::SslCredentialsOptions GetCredentialOptions();

 private:
  grpc::string token_;
  grpc::SslCredentialsOptions ssl_options;
};

#endif  // AUTHENTICATOR_HPP
