// ---------------- Dispense functions (separated) ----------------
void startDispenseQueue() {
  // Build queue from selectedQty: one entry per product with units >0
  dbg("[DISPENSE] Building queue...");
  dispQueueLen = 0;
  dispQueuePos = 0;
  for (int i = 0; i < 4; i++) {
    if (selectedQty[i] > 0) {
      DispItem di;
      di.index = i;
      di.units = selectedQty[i];
      di.unitTime = products[i].timeMs;
      dispQueue[dispQueueLen++] = di;
      dbg("[DISPENSE] queued " + String(products[i].name) + " units=" + String(di.units) + " unitMs=" + String(di.unitTime));
    }
  }
  if (dispQueueLen == 0) {
    dbg("[DISPENSE] nothing to dispense");
    return;
  }
  // Reset state and start first relay
  dispensing = true;
  dispRelayOn = false;
  dispUnitStartMs = 0;
  dbg("[DISPENSE] starting");
}

void processDispense() {
  // call frequently in loop()
  if (!dispensing) return;
  if (dispQueuePos >= dispQueueLen) {
    // finished
    dispensing = false;
    dbg("[DISPENSE] finished all items");
    // turn off all relays just in case
    for (int r = 0; r < 4; r++) digitalWrite(RELAY_PINS[r], LOW);
    return;
  }

  DispItem &cur = dispQueue[dispQueuePos];
  int idx = cur.index;

  if (!dispRelayOn) {
    // start relay for one unit
    digitalWrite(RELAY_PINS[idx], HIGH);
    dispRelayOn = true;
    dispUnitStartMs = millis();
    dbg("[DISPENSE] relay ON for product " + String(products[idx].name) + " (units left " + String(cur.units) + ")");
    return;
  } else {
    // check if unit time elapsed
    unsigned long now = millis();
    if (now - dispUnitStartMs >= cur.unitTime) {
      // finish unit
      digitalWrite(RELAY_PINS[idx], LOW);
      dispRelayOn = false;
      cur.units--;
      dbg("[DISPENSE] finished one unit of " + String(products[idx].name) + ", remaining units for this product: " + String(cur.units));
      if (cur.units <= 0) {
        dispQueuePos++;
        dbg("[DISPENSE] moving to next product (pos " + String(dispQueuePos) + ")");
      }
      // wait briefly (small gap) before next unit start — here we will allow next loop iteration to start next unit
    }
  }
}
