// Sets all the pertinent attributes for products
let processProducts = function() {
    let index = 0;
    app.products.map((product) => {
        Vue.set(product, 'index', index++);
        Vue.set(product, 'showReviews', false);
        Vue.set(product, 'otherReviews', []);
        Vue.set(product, 'yourReview', { rating: 0, numStars: 0 });
        Vue.set(product, 'show', true);
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

// This is where the data and the methods are declared for our Vue.
let app = new Vue({
    el: "#app",
    delimiters: ['${', '}'],
    unsafeDelimiters: ['!{', '}'],
    data: {
        products: [],

        starIndices: [1, 2, 3, 4, 5],

        loggedInUser: undefined,
        searchBar: ''
    },
    methods: {
        getYourReview: getYourReview,
        toggleReviewsSection: toggleReviewsSection,
        saveReview: saveReview,
        hoverStar: hoverStar,
        leaveStarRow: leaveStarRow,
        clickStar: clickStar,
        doSearch: doSearch
    }
});

onPageLoad();