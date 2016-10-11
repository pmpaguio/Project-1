
// catalog.hpp
// CSUF CPSC 131, Fall 2016, Project 1
//
// Classes that define a catalog of supermarket products.

#pragma once

#include <stdexcept>
#include <string>

// A product represents one particular kind of product, such as apples
// or cereal.
class Product {
public:
  // Create a product with a given code, name, and price.
  //
  // code is intended to be a UPC code (bar code) or PLU code in a
  // string.
  //
  // name may be any string.
  //
  // price is in units of dollars. It must be positive, or else this
  // function throws std::invalid_argument.
  Product(const std::string& code,
          const std::string& name,
          double price) {
    // TODO: implement this function properly
	  if (price < 0)
	  {
		  throw std::invalid_argument("Price must be positive");
	  }
	  this->code = code;
	  this->name = name;
	  this->price = price;
   // throw std::logic_error("not implemented yet");
  }

  ~Product() { }

  // Accessors.
  const std::string& getCode() const { return code; }
  const std::string& getName() const { return name; }
  double getPrice() const { return price; }
  
private:
  std::string code, name;
  double price;
  Product *prev;
  Product *next;
  friend class Catalog;
};

// A catalog represents a collection of all of the products available
// at a store.
class Catalog {
public:
  // Create a new catalog.
  //
  // maxProducts is the maximum number of products that can be
  // stored. It must be positive, or else this function throws
  // std::invalid_argument.
  Catalog(int maxProducts) {
    // TODO: implement this function properly
	  if (maxProducts <= 0)
	  {
		  throw std::invalid_argument("Max products must be greater than 0.");
	  }
	this->maxProducts = maxProducts;
	numProducts = 0;
	header = new Product(" ", " ", 0);
	trailer = new Product(" ", " ", 0);
	header->next = trailer;
	trailer->prev = header;
   // throw std::logic_error("not implemented yet");
  }
  
  ~Catalog() {
    // TODO: implement this function properly
	  Product* v = header->next;
	  for (int ix = 0; ix < numProducts; ix++)
	  {
		  Product* u = v->next;
		  delete v;
		  v = u;
	  }
   // throw std::logic_error("not implemented yet");
  }

  // Accessors.
  int getMaxProducts() const {
    // TODO: implement this function properly
	  return maxProducts;
    //throw std::logic_error("not implemented yet");
  }
  
  int getNumProducts() const {
    // TODO: implement this function properly
	  return numProducts;
   // throw std::logic_error("not implemented yet");
  }

  // Return true when the catalog cannot fit any more products.
  bool isFull() const {
    // TODO: implement this function properly
	  return numProducts >= maxProducts;
   // throw std::logic_error("not implemented yet");
  }

  // Add a new product to the catalog with a given code and name.
  //
  // code, name, and price have the same meaning as in a Product. If
  // price is invalid, throw std::invalid_argument.
  //
  // If this catalog is already full, throw overflow_error.
  //
  // Code must be different from all the product codes already in the
  // database. If it's not, throw std::invalid_argument.
  void addProduct(const std::string& code,
                  const std::string& name,
                  double price) {
    // TODO: implement this function properly
	  if (isFull())
	  {
		  throw std::overflow_error("Catalog is full.");
	  }
	  std::string tempCode=" ";
	  try {
		  tempCode = findCode(code).getCode();
	  }
	  catch (std::exception e)
	  { }
	  if (tempCode == code)
	  {
		  throw std::invalid_argument("Code already exists.");
	  }
	 
	  Product* v = header->next;
	  Product* u = new Product(code, name, price);
	  u->next = v;
	  u->prev = v->prev;
	  v->prev->next = u;
	  v->prev = u;
	  numProducts++;
  //  throw std::logic_error("not implemented yet");
  }

  // Find a product by its code.
  //
  // code is a product code.
  //
  // Returns a const reference to the product with the matching code.
  //
  // Throw std::invalid_argument if no product with that code exists
  // in the catalog.
  const Product& findCode(const std::string& code) const {
    // TODO: implement this function properly
	Product* v = header->next;
	for (int ix = 0; ix < numProducts; ix++)
	{
		if (v->code == code)
			return *v;
		v = v->next;
	}
	throw std::exception("Code not found.");
	return *header;
    //throw std::logic_error("not implemented yet");
  }

private:
  // TODO: add data members
	int maxProducts;
	int numProducts;
	Product* header;
	Product* trailer;
};
