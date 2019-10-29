/* Boilerplate importing snarky functions */
module Universe = (val Snarky_universe.default());
open! Universe.Impl;
open! Universe;

/* Here we are declaring that the "statement" or "public input"
   for our zk-SNARK is a single hash */
let statement = InputSpec.[(module Hash)];

/* Here we are declaring that the top-level "witness" for our
   zk-SNARK is a field element. */
module Witness = Field;

/* This is the definition of our zk-SNARK. We are saying

  "I know a value 'preimage' such that hash(preimage) is equal to
  the statement (or public input) h." */
let main = (preimage: Witness.t, h, ()) =>
  Field.assertEqual(Hash.hash([|preimage|]), h);

/* Finally we call runMain which sets our program up for use with
   snarkyjs */
runMain(statement, (module Witness), main);