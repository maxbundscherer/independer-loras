Cipher *i_cipher = new Cipher();

void crypt_init_cipher(char *key)
{
  i_cipher->setKey(key);
}

String crypt_encrypt(String msg)
{
  // return msg;
  // return base64_str_to_base64(i_cipher->encryptString(msg));
  return i_cipher->encryptString(msg);
}

String crypt_decrypt(String msg)
{
  // return msg;
  // return i_cipher->decryptString(base64_base64_to_str(msg));
  return i_cipher->decryptString(msg);
}