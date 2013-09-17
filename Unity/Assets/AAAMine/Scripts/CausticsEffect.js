#pragma strict

// Change renderer's material each changeInterval
// seconds from the material array defined in the inspector.
var materials : Material[];
var changeInterval = 0.2;

function Update () {
	if (materials.Length == 0) // do nothing if no materials
		return;

	// we want this material index now
	var index : int = Time.time / changeInterval;
	// take a modulo with materials count so that animation repeats
	index = index % materials.Length;

	// assign it to the renderer
	renderer.sharedMaterial = materials[index];
}