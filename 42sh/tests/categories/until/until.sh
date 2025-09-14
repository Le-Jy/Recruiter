condition="non"

until [ "$condition" = "oui" ]; do
    echo "La condition n'est pas remplie."
    
    condition="oui"
done

echo "La condition est maintenant remplie."

