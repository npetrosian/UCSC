def get_logged_in_user():
    user = None if auth.user is None else auth.user.email
    return response.json(dict(user=user))

def get_all_products():
    products = db(db.product).select()
    for product in products:
        product.avg_rating = 0
        sum = 0
        reviews = db((db.review.product_id == product.id) & (db.review.rating > 0)).select()
        for review in reviews:
            sum += review.rating
        if len(reviews) > 0:
            product.avg_rating = sum / len(reviews)
    return response.json(dict(products=products))

@auth.requires_login()
def get_your_review():
    review = db((db.review.product_id == request.vars.product_id) & (db.review.email == request.vars.email)).select().first()
    return response.json(dict(review=review))

@auth.requires_login()
def save_review():
    print(request.vars.product_id)
    print(request.vars.email)
    db.review.update_or_insert(
        ((db.review.product_id == request.vars.product_id) & (db.review.email == request.vars.email)),
        body=request.vars.body,
        product_id=request.vars.product_id
    )
    return "ok"

def get_other_reviews():
    if auth.user is None:
        other_reviews = db(db.review.product_id == request.vars.product_id).select()
    else:
        other_reviews = db( (db.review.product_id == request.vars.product_id) & (db.review.email != auth.user.email) ).select()
    
    return response.json(dict(other_reviews=other_reviews))

@auth.requires_login()
def update_star():
    db.review.update_or_insert(
        ((db.review.product_id == request.vars.product_id) & (db.review.email == request.vars.email)),
        rating=request.vars.rating,
        product_id=request.vars.product_id
    )
    # db.product.update_or_insert(
    #     db(db.review.product_id == request.vars.product_id).select()
    #     product.avg_rating = request.vars.avg_rating
    # )
    return "ok"

def get_cart(): 
    # Get the list of products in the shopping cart, with their quantities
    cart = db((db.review.email == auth.user.email)).select()
    return response.json(dict(cart=cart))

# def inc_cart():
    # Adds the specified quantity of the specified product to the cart 
    # (if the product is already in the cart, the quantity on order is incremented)

# def clear_cart():
    # Clears the shopping cart


