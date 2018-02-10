<template>
    <div class="ingredient-type">
        <div v-if="type === 'ALCOHOL'">
          <img src="../assets/rum.svg">
          <span v-if="label">Alcool</span>
        </div>
        <div v-else-if="type === 'MINERAL'">
          <img src="../assets/cooking-jar-to-measure-liquids.svg">
          <span v-if="label">Mineral</span>
        </div>
        <div v-else-if="type === 'SIRUP'">
          <img src="../assets/jelly-flask-container.svg">
          <span v-if="label">Sirup</span>
        </div>
        <div v-else-if="type === 'OTHER'">
          <img src="../assets/picnic-basket-full-of-raw-vegetables.svg">
          <span v-if="label">Other</span>
        </div>
        <div v-else>
          <img src="../assets/question-mark.svg">
          <span v-if="label">Unknown</span>
        </div>
    </div>
</template>

<script>
export default {
  props: ['type'],
  data () {
    return {
      label: false
    }
  },
  mounted () {
    this.label = !!this.$el.attributes.getNamedItem('label')
  }
}
</script>

<style scoped>
.ingredient-type img{
  vertical-align: middle;
  width: 40px;
}
.ingredient-type span {
  padding-left: 20px;
}
</style>
