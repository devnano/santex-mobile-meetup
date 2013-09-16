#pragma strict

var explosionParticleSystem:ParticleSystem;
var materialArray:Material[];

function Awake() {
	//define the color.
	var materialIndex:int = Random.Range(0, materialArray.Length);
	renderer.material = materialArray[materialIndex];

	explosionParticleSystem.startColor = renderer.material.color;
}

function Update () {

}

function OnCollisionEnter(collision : Collision) {
	Instantiate(explosionParticleSystem, transform.position, transform.rotation);

	Destroy(gameObject);
}
