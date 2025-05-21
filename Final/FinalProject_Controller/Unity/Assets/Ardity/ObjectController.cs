// ObjectController3D.cs
// Attach to your 3D object. Requires a SerialController in scene.
// Reads "X,Y|B" from Serial, applies Force + scaling.

using UnityEngine;

public class ObjectController3D : MonoBehaviour
{
    [Header("References")]
    [Tooltip("Drag your SerialController here")]
    [SerializeField] private SerialController serialController;

    [Header("Movement Settings")]
    [Tooltip("Force applied based on joystick (tune in Inspector)")]
    [SerializeField] private float moveForce = 100f;
    [Tooltip("Maximum linear speed")]
    [SerializeField] private float maxSpeed = 7f;
    [Tooltip("Linear drag to slow down")]
    [SerializeField] private float rigidbodyDrag = 1.5f;
    [Tooltip("Angular drag to prevent spin")]
    [SerializeField] private float angularDrag = 5f;
    [Tooltip("Small deadzone on normalized input (0–1)")]
    [SerializeField] private float unityDeadzone = 0.05f;

    [Header("Scale Settings")]
    [Tooltip("Scale at rest")]
    [SerializeField] private Vector3 normalScale = Vector3.one;
    [Tooltip("Scale when button pressed")]
    [SerializeField] private Vector3 enlargedScale = new Vector3(2f, 2f, 2f);

    private Rigidbody rb;
    private Vector3 currentMoveInput = Vector3.zero;
    private int currentButtonState = 0;

    void Start()
    {
        if (serialController == null)
        {
            serialController = FindAnyObjectByType<SerialController>();
            if (serialController == null)
            {
                Debug.LogError(
                  "SerialController not found. Assign it in the Inspector.", this
                );
                enabled = false;
                return;
            }
        }

        rb = GetComponent<Rigidbody>();
        if (rb == null)
        {
            Debug.LogWarning(
              "No Rigidbody found—adding one.", this
            );
            rb = gameObject.AddComponent<Rigidbody>();
        }

        rb.useGravity = false;
        rb.linearDamping = rigidbodyDrag;
        rb.angularDamping = angularDrag;
        rb.constraints = RigidbodyConstraints.FreezeRotation;

        Debug.Log(
          $"ObjectController3D initialized. " +
          $"Force={moveForce}, MaxSpeed={maxSpeed}, " +
          $"Drag={rigidbodyDrag}, AngularDrag={angularDrag}, " +
          $"UnityDeadzone={unityDeadzone}"
        );
    }

    void Update()
    {
        if (serialController == null) return;

        string message = serialController.ReadSerialMessage();
        if (message == null) return;

        Debug.Log($"UNITY RECEIVED RAW: <{message}>");

        try
        {
            var parts = message.Split('|');
            if (parts.Length != 2) return;
            var vals = parts[0].Split(',');
            if (vals.Length != 2) return;

            if (
              int.TryParse(vals[0], out int joyX) &&
              int.TryParse(vals[1], out int joyY) &&
              int.TryParse(parts[1], out int btn)
            )
            {
                float nx = joyX / 100f;
                float nz = joyY / 100f;
                Vector3 rawInput = new Vector3(nx, 0f, nz);

                if (rawInput.magnitude < unityDeadzone)
                    currentMoveInput = Vector3.zero;
                else
                    currentMoveInput = rawInput;

                currentButtonState = btn;
            }
        }
        catch
        {
            currentMoveInput = Vector3.zero;
            currentButtonState = 0;
        }
    }

    void FixedUpdate()
    {
        if (rb == null) return;

        if (currentMoveInput != Vector3.zero)
        {
            rb.AddForce(currentMoveInput * moveForce, ForceMode.Force);
        }

        if (rb.linearVelocity.magnitude > maxSpeed)
        {
            rb.linearVelocity = rb.linearVelocity.normalized * maxSpeed;
        }

        transform.localScale = (
          currentButtonState == 1 ? enlargedScale : normalScale
        );
    }
}
