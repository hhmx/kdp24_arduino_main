void execute(String cmd)
{
  cmd.trim();

  if (cmd == "")
  {
    // Serial.println("Serial for http response is available!");
    return;
  }
  else
  {
    // TYPICALLY, THE RESPONSE SIZE IS LESS THAN 500 BYTES (CHARACTERS), SO A VALUE OF 1024 IS FINE.
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, cmd);

    String status = doc["status"];

    if (flagDevelopment)
    {
      Serial.print(F("STATUS: "));
      Serial.println(status);
    }

    if (status == "success")
    {
      String did = doc["did"];
      String action = doc["action"];

      if (flagDevelopment)
      {
        Serial.print(F("DID: "));
        Serial.println(did);
        Serial.print(F("ACTION: "));
        Serial.println(action);
      }

      if (action == "open")
      {
        open(did);
      }
    }
    else if (status == "error")
    {
      String message = doc["message"];

      if (flagDevelopment)
      {
        Serial.print(F("MESSAGE: "));
        Serial.println(message);
      }
    }
    else
    {
      // DO NOTHING...
    }
  }
}

void open(String did)
{
  Serial.print(F("OPEN -> "));
  Serial.println(did);
}