#include <xxtea-lib.h>

void crypt_init_cipher(char *key)
{
  xxtea.setKey(key);
}

String crypt_encrypt(String msg)
{
  // return msg;
  // return base64_str_to_base64(...);

  // Serial.println("Got msg '" + msg + "'");
  String r = xxtea.encrypt(msg);
  // Serial.println("Got enc '" + r + "'");

  // Serial.println("Got Encrpted Start");

  // for (int i = 0; i < r.length(); i++)
  // {

  //   char myChar = r.charAt(i);

  //   for (int i = 7; i >= 0; i--)
  //   {
  //     byte bytes = bitRead(myChar, i);
  //     Serial.print(bytes, BIN);
  //   }

  //   Serial.println("");
  // }

  // Serial.println("Got Encrpted Stop");

  return r;
}

String crypt_decrypt(String msg)
{
  // return msg;
  // return base64_base64_to_str(...);

  // Serial.println("Got msg '" + msg + "'");
  String r = xxtea.decrypt(msg);
  // Serial.println("Got denc '" + r + "'");

  // Serial.println("Got DEncrpted Start");

  // for (int i = 0; i < r.length(); i++)
  // {

  //   char myChar = r.charAt(i);

  //   for (int i = 7; i >= 0; i--)
  //   {
  //     byte bytes = bitRead(myChar, i);
  //     Serial.print(bytes, BIN);
  //   }

  //   Serial.println("");
  // }

  // Serial.println("Got DEncrpted Stop");

  return r;
}