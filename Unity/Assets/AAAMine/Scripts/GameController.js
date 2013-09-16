#pragma strict

var bubbleSeedObject:GameObject;
var terrainTransform:Transform;

var bubbleInitialY:int = 10;

function Start () {
	InvokeRepeating("DropNewBubble", 1, 3);
}

function Update () {
	
}

/** Private methods. */

function DropNewBubble() {
	var bubbleToDrop:GameObject = Instantiate(bubbleSeedObject);

	bubbleToDrop.transform.position = CalculateRandomPosition();
	bubbleToDrop.rigidbody.useGravity = true;
}

private function CalculateRandomPosition():Vector3 {
	var xLimit:float = terrainTransform.renderer.bounds.size.x * 0.5;
	var randomX:float = Random.Range(-xLimit, xLimit);

	var zLimit:float = terrainTransform.renderer.bounds.size.z * 0.5;
	var randomZ:float = Random.Range(-zLimit, zLimit);

	return new Vector3(randomX, bubbleInitialY, randomZ);
}
