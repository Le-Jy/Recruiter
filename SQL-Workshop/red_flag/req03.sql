DELETE FROM public.epix_posts AS EP
USING public.epix_hashtags AS EH, public.people AS P, public.epix_accounts AS EA
WHERE
    EH.name = 'EndSurveillance' AND
    EH.id = EP.hashtag_id AND
    EP.author_id = EA.id AND
    EA.person_id = P.id

RETURNING
    P.first_name,
    P.last_name,
    EA.username,
    EP.body AS post_content
/*FROM
    public.epix_posts AS EP,
    public.epix_hashtags AS EH,
    public.people AS P,
    public.epix_accounts AS EA
WHERE
    EH.name = 'EndSurveillance' AND
    EH.id = EP.hashtag_id AND
    EP.author_id = EA.id AND
    EA.person_id = P.id*/
