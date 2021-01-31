// Sets all the pertinent attributes for products
let processProducts = function() {
    let index = 0;
    app.products.map((product) => {
        Vue.set(product, 'index', index++);
        Vue.set(product, 'showReviews', false);
        Vue.set(product, 'otherReviews', []);
        Vue.set(product, 'yourReview', { rating: 0, numStars: 0 });
        Vue.set(product, 'show', true);
        Vue.set(product, 'cart_quantity', 1);
    });
};

// Retrieves all products
let getAllProducts = function() {
    $.getJSON(getAllProductsUrl, function(response) {
        app.products = response.products;
        processProducts();
        console.log(app.products)
    });
};

// Retrieve the logged in user
let getLoggedInUser = function(callback) {
    $.getJSON(getLoggedInUserUrl, function(response) {
        app.loggedInUser = response.user;
        callback();
    });
};

// Callback for the search feature
let doSearch = function () {
    for(let i = 0; i < app.products.length; i++) {
        let product = app.products[i];
        if(product.name.toUpperCase().startsWith(app.searchBar.toUpperCase()) || app.searchBar == '') {
            product.show = true;
        }
        else {
            product.show = false;
        }
    }
}

// Identifies the logged in user and loads all the products 
let onPageLoad = function() {
    getLoggedInUser(function() {
        getAllProducts();
        // get_products();
        read_cart();
        $("#vue-div").show();
    });
};

// This allows the logged in user to retrieve their previously saved review.
let getYourReview = function(productIndex) {
    // exit the function if the user is not logged in
    if (app.loggedInUser == undefined) {
        return;
    }

    let product = app.products[productIndex];

    $.getJSON(getYourReviewUrl, { product_id: product.id, email: app.loggedInUser }, function(response) {
        if (response.review != null) {
            product.yourReview = response.review;
            product.yourReview.rating = response.review.rating;
            product.yourReview.numStars = response.review.rating;
        }
        Vue.set(product.yourReview, 'hasBeenSaved', false);
    });
};

// This takes care of the functionality to see the reviews of other users. 
let getOtherReviews = function(productIndex) {
    let product = app.products[productIndex];
    $.getJSON(getOtherReviewsUrl, { product_id: product.id }, function(response) {
        product.otherReviews = response.other_reviews;
    });
};

// The review section closes once the close button is clicked
let closeReviews = function(productIndex) {
    let product = app.products[productIndex];
    product.showReviews = false;
}

// As the user toggles from one review to another, it expands the pertinent review
// and closes the previous ones
let toggleReviewsSection = function(productIndex) {
    let product = app.products[productIndex];
    product.showReviews = true;
    curr = 0;
    for(let i = 0; i < app.products.length; i++) {
        // if(curr != app.products[productIndex])
        if(i != productIndex) {
            app.products[i].showReviews = false;
        }
    }
    // products[productIndex].showReviews = true;
};

// Do this when a review is saved. Defines the functionality 
// when the user clicks on the save button. 
let saveReview = function(productIndex) {
    // exit the function if the user is not logged in
    if (app.loggedInUser == undefined) {
        return;
    }

    let product = app.products[productIndex];
    let yourReview = product.yourReview;
    yourReview.hasBeenSaved = false;

    $.post(saveReviewUrl, {

        product_id: product.id,
        email: app.loggedInUser,
        body: yourReview.body
    }, function(response) {
        yourReview.hasBeenSaved = true;
        setTimeout(function() {
            yourReview.hasBeenSaved = false;
        }, 1000);
    });
};

// Hover in functionality. Do this when hovering into the stars
let hoverStar = function(productIndex, starNum) {
    let product = app.products[productIndex];
    product.yourReview.numStars = starNum;
};

// Hover out functionality. Do this when hovering out of stars
let leaveStarRow = function(productIndex) {
    let product = app.products[productIndex];
    product.yourReview.numStars = product.yourReview.rating;
};

// Process actions when a star is clicked including averaging the ratings
let clickStar = function(productIndex, starNum) {
    let product = app.products[productIndex];
    product.yourReview.rating = starNum;
    $.post(updateStarUrl, {
        product_id: product.id,
        email: app.loggedInUser,
        rating: starNum
    }, function() {
        let sum = 0
        let length = product.otherReviews.length + 1;
        for (let i = 0; i < product.otherReviews.length; i++) {
            if (product.otherReviews[i].rating == 0) {
                length--;
            } else {
                sum += product.otherReviews[i].rating;
            }
        }
        if (product.yourReview.rating == 0) {
            length --;
        } else {
            sum += product.yourReview.rating;
        }

        product.avg_rating = sum / length;
    });
};

let extend = function(a, b) {
    for (var i = 0; i < b.length; i++) {
        a.push(b[i]);
    }
};

// Enumerates an array.
let enumerate = function(v) {
    var k=0;
    return v.map(function(e) {e._idx = k++;});
};

// let get_products = function () {
// Gets new products in response to a query, or to an initial page load.
    // $.getJSON(products_url, $.param({q: app.product_search}), function(data) {
        // app.products = data.products;
        // enumerate(app.products);
    // });
// };

// stores the cart locally
let store_cart = function() {
    localStorage.cart = JSON.stringify(app.cart);
};

// reads the cart locally
let read_cart = function() {
    // $.getJSON(getCartUrl, function(data) {...});
    // if (app.loggedInUser == undefined) {
        // return;
    // }
// 
    // let product = app.products[productIndex];
// 
    // $.getJSON(getCartUrl, function(response) {
        // if (response.cart != null) {
            // app.cart = response.cart;
        // }
// 
        // for(let i = 0; i < app.cart.length; i++) {
        //     shopping_cart.
        // }
// 
        // Vue.set(product.yourReview, 'hasBeenSaved', false);
    // });
// 

        if (localStorage.cart) {
            app.cart = JSON.parse(localStorage.cart);
        } else {
            app.cart = [];
        }
        update_cart();
};

// Increments and decrements the desired quantity of the cart
let inc_desired_quantity = function(product_idx, qty) {
        // Inc and dec to desired quantity.
        var p = app.products[product_idx];
        p.desired_quantity = Math.max(0, p.desired_quantity + qty);
        p.desired_quantity = Math.min(p.quantity, p.desired_quantity);
};

// Increments and decrements the cart quantity 
let inc_cart_quantity = function(p, qty) {
        // Inc and dec to desired quantity.
        console.log("Increment cart quantity clicked");
        // var p = app.cart[product_idx];
        p.cart_quantity = Math.max(0, p.cart_quantity + qty);
        p.cart_quantity = Math.min(p.quantity, p.cart_quantity);
        console.log("cart q is now " + p.cart_quantity);
        update_cart();
        store_cart();
};

// updates the cart size and cart total
let update_cart = function() {
        enumerate(app.cart);
        var cart_size = 0;
        var cart_total = 0;
        for (var i = 0; i < app.cart.length; i++) {
            var q = app.cart[i].cart_quantity;
            if (q > 0) {
                cart_size++;
                cart_total += q * app.cart[i].price;
            }
        }
        console.log('size');
        console.log(cart_size);
        console.log('total');
        console.log(cart_total);
        console.log('cart');
        console.log(app.cart);
        app.cart_size = cart_size;
        app.cart_total = cart_total;
};

// executed when the Buy button is enabled. It checks if the product 
// to be bought is already present in the cart. Otherwise, it adds the 
// product to the cart. 
let buy_product = function(p) {
        // I need to put the product in the cart.
        // Check if it is already there.
        var already_present = false;
        var found_idx = 0;
        console.log('cart');
        console.log(app.cart);
        for (var i = 0; i < app.cart.length; i++) {
            if (app.cart[i].id === p.id) {
                already_present = true;
                found_idx = i;
            }
        }
        // If it's there, just replace the quantity; otherwise, insert it.
        if (!already_present) {
            found_idx = app.cart.length;
            app.cart.push(p);
        }
        app.cart[found_idx].cart_quantity = p.cart_quantity;
        console.log("cart q is now " + app.cart[found_idx].cart_quantity);
        // Updates the amount of products in the cart.
        update_cart();
        store_cart();
};

    // app.customer_info = {}

// enables the stripe functionality 
let goto = function (page) {
        app.page = page;
        if (page == 'cart') {
            // prepares the form.
            app.stripe_instance = StripeCheckout.configure({
                key: 'pk_test_nj0aqiNoiqmy9UDJUILfP6OU00p6Ehzy2d',    //put your own publishable key here
                image: 'https://stripe.com/img/documentation/checkout/marketplace.png',
                locale: 'auto',
                token: function(token, args) {
                    console.log('got a token. sending data to localhost.');
                    app.stripe_token = token;
                    app.customer_info = args;
                    send_data_to_server();
                }
            });
        };

};

// enabled when the user selects the Pay button. This opens a modal in stripe that takes
// the user to the checkout page of paying
let pay = function () {
        app.stripe_instance.open({
            name: "Your Shopping Cart",
            description: "Please fill out the following:",
            billingAddress: true,
            shippingAddress: true,
            amount: Math.round(app.cart_total * 100),
        });
};

// calls the server and determines whether the transaction was successful or not
let send_data_to_server = function () {
        console.log("Payment for:", app.customer_info);
        // Calls the server.
        $.post(purchase_url,
            {
                customer_info: JSON.stringify(app.customer_info),
                transaction_token: JSON.stringify(app.stripe_token),
                amount: app.vue.cart_total,
                cart: JSON.stringify(app.cart),
            },
            function (data) {
                if (data.result === "ok") {
                    // The order was successful.
                    app.cart = [];
                    update_cart();
                    store_cart();
                    app.goto('prod');
                    $.web2py.flash("Thank you for your purchase");
                } else {
                    $.web2py.flash("The card was declined.");
                }
            }
        );
};

// This is where the data and the methods are declared for our Vue.
let app = new Vue({
    el: "#app",
    delimiters: ['${', '}'],
    unsafeDelimiters: ['!{', '}'],
    data: {
        products: [],
        starIndices: [1, 2, 3, 4, 5],
        loggedInUser: undefined,
        searchBar: '',
        cart: [],
        product_search: '',
        cart_size: 0,
        cart_total: 0,
        page: 'prod'
    },
    methods: {
        getYourReview: getYourReview,
        toggleReviewsSection: toggleReviewsSection,
        saveReview: saveReview,
        hoverStar: hoverStar,
        leaveStarRow: leaveStarRow,
        clickStar: clickStar,
        doSearch: doSearch,
        // get_products: get_products,
        inc_desired_quantity: inc_desired_quantity,
        inc_cart_quantity: inc_cart_quantity,
        buy_product: buy_product,
        goto: goto,
        pay: pay,
        update_cart: update_cart,
        store_cart: store_cart,
        send_data_to_server: send_data_to_server
    }
});

onPageLoad();