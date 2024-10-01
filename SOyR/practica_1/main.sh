#!/bin/bash

# nombre, precio y cantidad

PRODUCTS=inventario.txt

clear
display_menu() {
  printf "(Para salir de los menus de listas hay que apretar la letra 'q')\n\n"
  echo "1) Añadir producto"
  echo "2) Mostrar los productos"
  echo "3) Buscar producto por nombre"
  echo "4) Ver productos por precio"
  echo "-)"
  echo "9) Borrar TODOS los productos"
  echo "-)"
  echo "s) Salir"
  echo ""
  read -p "(1/2/3/4/5/s): " ans;

  case $ans in
    1)
      clear; add_product;;
    2)
      cat $PRODUCTS | less; clear;;
    3)
      search_product; clear;; 
    4)
      display_product_by_price; clear;; 
    9)
      clear_products;; 
    s|S)
      exit;; 
    *)
      clear;;
  esac

  display_menu
}

add_product() {
  echo "Añadiendo nuevo producto"

  # leo el nombre del producto y corroboro que este bien
  pname=""
  while [ -n "$(echo "$pname" | grep -o '[0-9]*')" ] || [ -z "$pname" ]; do
    read -p "nombre del producto: " pname
    if [ -z "$pname" ]; then
      echo " "
      echo "ERROR: Debe ingresar un valor"
      echo " "
      echo " "
    elif [ -n "$(echo "$pname" | grep -o '[0-9]*')" ]; then
      echo " "
      echo "ERROR: '$pname' tiene que ser un nombre válido (solo letras)"
      echo " "
      echo " "
    fi
  done

  # leo el precio del producto y corroboro que esté bien (solo numeros y mayor que cero)
  pprice=""
  while [ -n "$(echo "$pprice" | grep -Eo '\b[a-zA-Z]+\b')" ] || [ -z "$pprice" ]; do
    read -p "precio de '$pname': " pprice
    if [ -z "$pprice" ]; then
      echo " "
      echo "ERROR: Debe ingresar un valor"
      echo " "
      echo " "
    elif [ -n "$(echo "$pprice" | grep -Eo '\b[a-zA-Z]+\b')" ]; then
      echo " "
      echo "ERROR: '$pprice' tiene que ser un valor válido (solo números y mayor que cero)"
      echo " "
      echo " "
    fi
  done

  # leo la cantidad de productos y corroboro que esté bien (solo numeros y mayor que cero)
  pquant=""
  while [ -n "$(echo "$pquant" | grep -Eo '\b[a-zA-Z]+\b')" ] || [ -z "$pquant" ]; do
    read -p "cantidad de '$pname': " pquant
    if [ -z "$pquant" ]; then 
      echo " "
      echo "ERROR: Debe ingresar un valor"
      echo " "
      echo " "
    elif [ -n "$(echo "$pquant" | grep -Eo '\b[a-zA-Z]+\b')" ]; then
      echo " "
      echo "ERROR: '$pquant' tiene que ser una cantidad válida (solo números y mayor que cero)"
      echo " "
      echo " "
    fi
  done

  clear
  echo "$pname, $pprice, $pquant" >> $PRODUCTS
  echo "'$pname' añadido correctamente"
  echo ""
}

clear_products() {
  read -p "Desea limpiar al lista de productos completamente? [s/n] " choice
  case $choice in
    s|S)
      clear
      echo "" > $PRODUCTS
      echo " "
      echo "Se borraron todos los productos"
      echo " "
      echo " ";;
    *)
      clear;;
  esac
}

search_product() {
  read -p "Buscar producto por nombre: " pname
  linenumber=$(cat $PRODUCTS | cut -d',' -f1 | grep -m 1 -n "$pname" | cut -d':' -f1)
  echo "$linenumber" | xargs -I'{}' sed '{}q;d' $PRODUCTS | less
}

display_product_by_price() {
  cat $PRODUCTS | cut -d',' -f2 | sort -n -r | less
}

display_menu
