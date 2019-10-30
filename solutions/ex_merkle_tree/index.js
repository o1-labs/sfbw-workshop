const { bn128 } = require('snarkyjs-crypto');
const Snarky = require("snarkyjs");
const snarky = new Snarky("./ex_merkle_tree.exe");

const depth = 8;
const numElts = Math.pow(2, depth);
const data = []

for (let i = 0; i < numElts; ++i) {
  data.push(bn128.Field.ofInt(i));
}

/* No need to hash leaves which are already field elements */
const hashElt = (x) => x;
const defaultElt = bn128.Field.ofInt(0);

const tree = bn128.MerkleTree.ofArray(hashElt, defaultElt, data);

const root = bn128.MerkleTree.root(tree);
const indexToProve = 17;
const merkleProof = bn128.MerkleTree.MembershipProof.create(tree, indexToProve);

const statement = [
  /* Root hash */
  root,
  /* Data */
  data[indexToProve]
];

snarky.prove({
  statement: statement,
  witness: [
    merkleProof.index,
    merkleProof.path
  ]
}).then((proof) => {
  console.log("Created proof:\n" + proof + "\n");
  return snarky.verify({
    statement: statement,
    proof: proof
  });
}, console.log).then((verified) => {
  console.log("Was the proof verified? " + verified);
  if (verified) {
    process.exit(0);
  } else {
    process.exit(1);
  }
},() => { process.exit(1); });
