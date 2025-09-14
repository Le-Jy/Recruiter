UPDATE public.epix_posts
SET downvotes = (SELECT upvotes * (SELECT AVG(downvotes::float/upvotes::float) 
            FROM public.epix_posts
            WHERE author_id = 933 AND id != 139)
FROM public.epix_posts
WHERE id = 139)
WHERE id = 139
